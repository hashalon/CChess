#include "board.h"

#include "vector.h"
#include "piece.h"

board * make_board () {

	// create a new board that will survive
	// out of the scope of this function
	board * b = malloc(sizeof(board));

	// order of pieces
	int o = {ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK};

	// fill both row with pawns
	for (int i = 0, j = 0; i < SIZE; ++i) {
		b->pieces[j++] = make_piece(i,0,WHITE,o[i]);
		b->pieces[j++] = make_piece(i,1,WHITE,PAWN);
		b->pieces[j++] = make_piece(i,6,BLACK,PAWN);
		b->pieces[j++] = make_piece(i,7,BLACK,o[i]);
	}
	return b;
}

char valid (vec2 p) {
	return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
}

int find (board * b, vec2 p) {
	for (int i = 0; i < b->nb_pieces; ++i) {
		if (equ(b->pieces[i].pos, p))
			return i;
	}
	return -1; // failed to find
}

char remove (board * b, vec2 p) {
	int i = find(b, p);
	if (i < 0) return 0; // failed to remove

	// take last piece and overwrite at index found and reduce array size
	b->pieces[i] = b->pieces[--b->nb_pieces];
	return 1;
}

char move (board * b, vec2 p, vec2 d) {
	int i = find(b, p);
	if (i < 0) return 0; // failed to move

	// try to remove at destination
	remove(b, d);

	// change the position of the piece
	b->pieces[i].pos = d;
	return 1;
}


int get_moves (board * b, char t, vec2 p, vec2 o[NB_CELLS]) {
	int i = find(b, p);
	if (i < 0) return -1; // failed to find piece

	// check that the piece is of the correct team
	piece q = b->pieces[i];
	if (t != q.team) return -2; // incorrect team

	// test type of piece to find possible moves
	switch (q.type) {
	case PAWN   : return moves_pawn  (b, q, o);
	case ROOK   : return moves_rook  (b, q, o);
	case KNIGHT : return moves_knight(b, q, o);
	case BISHOP : return moves_bishop(b, q, o);
	case QUEEN  : return moves_queen (b, q, o);
	case KING   : return moves_king  (b, q, o);
	}
	return -3; // invalid type
}
