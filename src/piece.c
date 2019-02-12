#include "piece.h"

#include "macro.h"
#include "vector.h"
#include "move.h"
#include "board.h"

// type definitions
typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

#define SET      64
#define LEFT      0
#define RIGHT     1
#define NB_LEFT   3
#define NB_RIGHT  2

/* STATIC ARRAYS */
static vec2 ORTH [4] = {{ 1, 0}, { 0, 1}, {-1, 0}, { 0,-1}};
static vec2 DIAG [4] = {{ 1, 1}, {-1, 1}, {-1,-1}, { 1,-1}};
static vec2 JUMP [8] = {{ 2, 1}, {-2, 1}, {-2,-1}, { 2,-1},
                        { 1, 2}, {-1, 2}, {-1,-2}, { 1,-2}};

static char CAST_LEFT  [NB_LEFT ] = {1,2,3};
static char CAST_RIGHT [NB_RIGHT] = {5,6};

// helpers function for building a set of possible moves
static int get_moves_pawn     (board*, piece, move*);
static int get_pawn_side_move (board*, piece, move*, int, vec2);
static int get_moves_leaper   (board*, piece, move*, int, vec2*, int);
static int get_moves_rider    (board*, piece, move*, int, vec2*, int);
static int get_king_castling  (board*, piece, move*, int, char);
static int add_to_set         (vec2  , piece, move*, int);

/* PUBLIC FUNCTIONS */

// helper to create a new piece
piece make_piece (int x, int y, int team, int type) {
	piece  piece = {make_vector(x,y), team, type, NO};
	return piece;
}

// get possible moves for this piece
// store them into the out array and return number of moves found
int get_moves(board * board, piece piece, move * out) {
	int count;
	switch (piece.type) {
		case PAWN   : return get_moves_pawn   (board, piece, out);
		case ROOK   : return get_moves_rider  (board, piece, out, 0, ORTH, 4);
		case KNIGHT : return get_moves_leaper (board, piece, out, 0, JUMP, 8);
		case BISHOP : return get_moves_rider  (board, piece, out, 0, ORTH, 4);
		case QUEEN  :
			count = get_moves_rider (board, piece, out,     0, ORTH, 4);
			return  get_moves_rider (board, piece, out, count, DIAG, 4);
		case KING   :
			count = get_moves_leaper(board, piece, out,     0, ORTH, 4);
			count = get_moves_leaper(board, piece, out, count, DIAG, 4);
			if (piece.hasMoved) return count;

			// test each rook to check for castling...
			count = get_king_castling(board, piece, LEFT , count, out);
			return  get_king_castling(board, piece, RIGHT, count, out);
	}
	return 0;
}

piece null_piece () {
	piece piece = {null_vector(), -1, -1};
	return piece;
}
char is_null_piece(piece piece) {
	return is_null_vector(piece.pos)
			|| (piece.team < WHITE || BLACK < piece.team)
			|| (piece.type < PAWN  || KING  < piece.type);
}

/* PRIVATE FUNCTIONS */

static int get_moves_pawn (board * board, piece piece, move * out) {
	int  count = 0;
	char f = piece.team ? -1 :  1; // define forward based on team

	// prepare positions to test:
	// - forward
	// - long forward
	// - left
	// - right
	vec2
		posf = piece.pos,
		posF = piece.pos,
		posl = piece.pos,
		posr = piece.pos;
	posf.y += f; posF.y += f*2;
	posl.y += f; posl.x -= 1;
	posr.y += f; posr.x += 1;

	// no piece forward !
	struct piece target = find(board, posf);
	if (is_null_piece(target)) {
		count = add_to_set(posf, target, out, count);

		// test long move
		target = find(board, posF);
		if (!piece.hasMoved && is_null_piece(target)) {
			move L = make_longmove(posF);
			out[count++] = L;
		}
	}

	// repeat the same operation twice
	// we use a second function for convenience
	count = get_pawn_side_move(board, piece, out, count, posl);
	return  get_pawn_side_move(board, piece, out, count, posr);
}

// test pawn side move (call twice for left and right)
static int get_pawn_side_move (
		board * board, piece pawn,
		move  * out  , int   size, vec2 dest
) {

	piece target = find(board, dest);
	if (!is_valid(dest)) return size;

	// try direct capture
	if (!is_null_piece(target)) {
		if (target.team != pawn.team)
			size = add_to_set(dest, target, out, size);
	}
	// try en passant capture
	else if (!is_null_holder(board->prev_long) && equ(board->prev_long.dest, dest)) {
		size = add_to_set(dest, target, out, size);
	}

	return size;
}


/*
 * Pass:
 * - the board to test
 * - the initial position of the piece
 * - the team of the piece
 * - the directions to test
 * - the set of moves to fill
 * */
static int get_moves_leaper (
		board * board, piece piece,
		move  * out  , int size_out,
		vec2  * dirs , int size_dirs
) {
	for (int i=0; i < size_dirs; ++i) {
		vec2 dir = dirs[i];

		// test position
		vec2 pos2 = add(piece.pos, dir);
		if (is_valid(pos2)) {

			// find the piece at the location
			struct piece target = find(board, pos2);

			// no other piece at location or enemy piece
			if (
				is_null_piece(target) ||
				target.team != piece.team
			)
				size_out = add_to_set(pos2, target, size_out, out);
		}
	}
	return size_out;
}

static int get_moves_rider (
		board * board, piece piece,
		move  * out  , int size_out,
		vec2  * dirs , int size_dirs
) {
	for (int i=0; i < size_dirs; ++i) {
		vec2 dir = dirs[i];

		// test position
		vec2 pos2 = add(piece.pos, dir);
		while (is_valid(pos2)) {

			// find the piece at the location
			struct piece target = find(board, pos2);

			// no other piece at location or enemy piece
			if (is_null_piece(target)) {
				size_out = add_to_set(pos2, target, size_out, out);
			}
			else if (target.team != piece.team) {
				size_out = add_to_set(pos2, target, size_out, out);
				break;
			}
			else break;

			// move to next position
			pos2 = add(pos2, dir);
		}
	}
	return size_out;
}

// test king castling move (call twice for left and right)
static int get_king_castling  (
		board * board, piece king,
		move  * out  , int   size, char side
) {
	char y = king.team ? 7 : 0;
	char x = side      ? 7 : 0;
	vec2 rook_pos = {0, y};

	piece rook = find(board, rook_pos);
	if (
		is_null_piece(rook)    ||
		rook.team != king.team ||
		rook.hasMoved
	)
		return size;

	// test positions between king and rook
	// all cells must be free between them
	char * poss = side ? CAST_RIGHT : CAST_LEFT ;
	int    nb   = side ? NB_RIGHT   : NB_LEFT   ;
	for (int i=0; i < nb; ++i) {

		vec2  pos  = {poss[i], y};
		piece cell = find(board, cell.pos);
		if (!is_null_piece(cell)) return size;
	}

	// all cells are free => add castling
	vec2
		dest1 = {side ? 6 : 2, y},
		dest2 = {side ? 5 : 3, y};
	move m = make_castling(dest1, dest2, rook);
	out[size++] = m;
	return size;
}

// simply add the
static int add_to_set(vec2 pos, piece target, move * out, int size) {
	move move = make_move(pos, target);
	out[size++] = move;
	return size;
}
