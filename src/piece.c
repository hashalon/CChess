#include "piece.h"

#include "macro.h"
#include "vector.h"
#include "move.h"
#include "board.h"

#define D4 4
#define D8 8
#define SET 64

#define LEFT  0
#define RIGHT 1

#define P_L 3
#define P_R 2

// type definitions
typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

/* Encapsulation */
static vec2 D_orth[D4] = {{ 1, 0}, { 0, 1}, {-1, 0}, { 0,-1}};
static vec2 D_diag[D4] = {{ 1, 1}, {-1, 1}, {-1,-1}, { 1,-1}};
static vec2 D_jump[D8] = {{ 2, 1}, {-2, 1}, {-2,-1}, { 2,-1},
                          { 1, 2}, {-1, 2}, {-1,-2}, { 1,-2}};
static int moves_leaper (board*, vec2, char, int, vec2[], int, move[]);
static int moves_rider  (board*, vec2, char, int, vec2[], int, move[]);
static int add_to_set   (vec2, piece, int, move[]); // helper

// helper functions for pawn side moves and king castling
static int pawn_side_move (board*, piece, vec2, int, vec2[]);
static int king_castling  (board*, piece, char, int, vec2[]);

static char P_left [P_L] = {1,2,3};
static char P_right[P_R] = {5,6};

piece make_piece (int x, int y, int team, int type) {
	piece  p = {vector(x,y), team, type, NO};
	return p;
}

int moves_pawn (board*b, piece p, move o[SET]) {
	int  s = 0;
	char f = p.team ? -1 : 1; // define forward based on team

	// prepare positions to test
	vec2 posf = p.pos, posl = p.pos, posr = p.pos, posF = p.pos;
	posf.y += f; posl.y += f; posr.y += f; posF.y += f*2;
	posl.x -= 1; posr.x += 1;

	// no piece forward !
	piece target = find(b, posf);
	if (is_free_piece(target)) {
		s = add_to_set(posf, target, s, o);

		// test long move
		target = find(b, posF);
		if (!p.hasMoved && is_free_piece(target)) {
			move L = make_longmove(posF);
			o[s++] = L;
		}
	}

	// repeat twice
	s = pawn_side_move(b, p, posl, s, o);
	s = pawn_side_move(b, p, posr, s, o);

	return s;
}
int moves_rook   (board*b, piece p, move o[SET]) {
	return moves_rider (b, p.pos, p.team, D4, D_orth, 0, o);
}
int moves_knight (board*b, piece p, move o[SET]) {
	return moves_leaper(b, p.pos, p.team, D8, D_jump, 0, o);
}
int moves_bishop (board*b, piece p, move o[SET]) {
	return moves_rider (b, p.pos, p.team, D4, D_diag, 0, o);
}
int moves_queen  (board*b, piece p, move o[SET]) {
	int s = 0;
	s = moves_rider (b, p.pos, p.team, D4, D_orth, s, o);
	s = moves_rider (b, p.pos, p.team, D4, D_diag, s, o);
	return s;
}
int moves_king   (board*b, piece p, move o[SET]) {
	int s = 0;
	s = moves_leaper(b, p.pos, p.team, D4, D_orth, s, o);
	s = moves_leaper(b, p.pos, p.team, D4, D_diag, s, o);

	// check for castling...
	if (p.hasMoved) return s;

	// test each rook
	s = king_castling(b, p, LEFT , s, o);
	s = king_castling(b, p, RIGHT, s, o);

	return s;
}

piece no_piece () {
	piece p = {invalid_vector(), -1, -1};
	return p;
}
char is_free_piece(piece p) {
	return is_free(p.pos)
			|| (p.team < WHITE || BLACK < p.team)
			|| (p.type < PAWN  || KING  < p.type);
}

/*
 * Pass:
 * - the board to test
 * - the initial position of the piece
 * - the team of the piece
 * - the directions to test
 * - the set of moves to fill
 * */
static int moves_leaper (
		board*board, vec2 pos, char team,
		int sd, vec2 dirs[D8  ],
		int so, move out [SET])
{
	for (int i=0; i < sd; ++i) {
		vec2 dir = dirs[i];

		// test position
		vec2 pos2 = add(pos, dir);
		if (valid(pos2)) {

			// find the piece at the location
			piece target = find(board, pos2);

			// no other piece at location or enemy piece
			if (is_free_piece(target) || target.team != team)
				so = add_to_set(pos2, target, so, out);
		}
	}
	return so;
}
static int moves_rider (
		board*board, vec2 pos, char team,
		int sd, vec2 dirs[D8  ],
		int so, move out [SET])
{
	for (int i=0; i < sd; ++i) {
		vec2 dir = dirs[i];

		// test position
		vec2 pos2 = add(pos, dir);
		while (valid(pos2)) {

			// find the piece at the location
			piece target = find(board, pos2);

			// no other piece at location or enemy piece
			if (is_free_piece(target))
				so = add_to_set(pos2, target, so, out);
			else if (target.team != team) {
				so = add_to_set(pos2, target, so, out);
				break;
			} else break;

			// move to next position
			pos2 = add(pos2, dir);
		}
	}
	return so;
}
// simply add the
static int add_to_set(vec2 pos, piece target, int size, move out[SET]) {
	move m = make_move(pos, target);
	out[size++] = m;
	return size;
}

// test pawn side move (call twice for left and right)
static int pawn_side_move (board * b, piece pawn, vec2 pos, int s, vec2 out[SET]) {

	piece target = find(b, pos);
	if (!valid(pos)) return s;

	// try capture on the side
	if (!is_free_piece(target)) {
		if (target.team != pawn.team)
			s = add_to_set(pos, target, s, out);
	} else if (b->prevLong != NULL && equ(b->prevLong->dest, pos)) // en passant
		s = add_to_set(pos, target, s, out); // capture en passant
	return s;
}

static int king_castling  (board * b, piece king, char side, int s, vec2 out[SET]) {
	char y = king.team ? 7 : 0;
	char x = side      ? 7 : 0;
	vec2 rook_pos = {0, y};

	piece rook = find(b, rook_pos);
	if (is_free_piece(rook) || rook.team != king.team || rook.hasMoved) return s;

	// test positions between king and rook
	// all cells must be free between them
	char * poss = side ? P_right : P_left;
	int  nb     = side ? P_R     : P_L;
	for (int i=0; i < nb; ++i) {
		vec2  pos  = {poss[i], y};
		piece cell = find(b, cell.pos);
		if (!is_free_piece(cell)) return s;
	}

	// all cells are free => add castling
	vec2
		dest1 = {side ? 6 : 2, y},
		dest2 = {side ? 5 : 3, y};
	move m = make_castling(dest1, dest2, rook);
	out[s++] = m.dest;

	return s;
}
