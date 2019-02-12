#include "board.h"

#include "macro.h"
#include "vector.h"
#include "piece.h"
#include "move.h"

typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

// encapsulated
static int  find_index     (board*, vec2);
static void displace_piece (board*, piece, vec2);

board * make_board () {

	// create a new board that will survive
	// out of the scope of this function
	board * b = malloc(sizeof(board));

	// order of pieces
	int o[] = {ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK};

	// fill both row with pawns
	for (int i = 0, j = 0; i < SIZE; ++i) {
		b->pieces[j++] = make_piece(i,0,WHITE,o[i]);
		b->pieces[j++] = make_piece(i,1,WHITE,PAWN);
		b->pieces[j++] = make_piece(i,6,BLACK,PAWN);
		b->pieces[j++] = make_piece(i,7,BLACK,o[i]);
	}
	b->nb_pieces = MAX_PIECES;
	b->prev_long = null_holder();

	return b;
}

board * clone(board * board0) {

	// copy content of board into an new one
	board * board1 = malloc(sizeof(board));
	for (int i=0; i < board0->nb_pieces; ++i) {
		board1->pieces[i] = board0->pieces[i];
	}
	board1->nb_pieces = board0->nb_pieces;
	board1->prev_long = board0->prev_long;
	return board1;
}

piece find (board * board, vec2 pos) {
	int i = find_index(board, pos);
	if (i < 0) return null_piece(); // failed to find
	return board->pieces[i];
}

char is_valid (vec2 pos) {
	return 0 <= pos.x && pos.x < SIZE && 0 <= pos.y && pos.y < SIZE;
}

char remove_piece (board * board, vec2 pos) {
	int i = find_index(board, pos);
	if (i < 0) return NO; // failed to remove

	// take last piece and overwrite at index found and reduce array size
	board->pieces[i] = board->pieces[ --board->nb_pieces ];
	return YES;
}

/*
int get_moves (board * board, char team, vec2 pos, move * out) {
	int i = find_index(board, pos);
	if (i < 0) return -1; // failed to find piece

	// check that the piece is of the correct team
	piece piece = board->pieces[i];
	if (team != piece.team) return -2; // incorrect team

	// TODO...
} // */

void move_piece (board * board, piece piece, move move) {
	// remove target
	remove_piece(board, move.target.pos);

	// move current piece
	displace_piece(board, piece, move.dest);

	// if long move, store info in the board
	if (move.isLong) {
		board->prev_long = make_holder(move.dest, piece);
	}
	// if castling
	else if (move.ext != NULL) {
		displace_piece(board, move.ext->target, move.ext->dest);
	}
}

void draw_board (board * b) {

}

/* PRIVATE FUNCTIONS */

static int find_index (board * board, vec2 pos) {
	for (int i = 0; i < board->nb_pieces; ++i) {
		if (equ(board->pieces[i].pos, pos))
			return i;
	}
	return -1; // failed to find
}

static void displace_piece (board * board, piece piece, vec2 dest) {
	int i = find_index(board, dest);
	if (i < 0) return;

	piece.pos      = dest;
	piece.hasMoved = YES;
	board->pieces[i] = piece;
}


/*char move_pos (board * b, vec2 p, vec2 d) {
	int i = find_index(b, p);
	if (i < 0) return NO; // failed to move

	// try to remove at destination
	remove(b, d);

	// change the position of the piece
	piece q = b->pieces[i];
	q.pos      = d;
	q.hasMoved = YES;
	b->pieces[i] = q;
	return YES;
}*/
