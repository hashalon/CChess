#include "board.h"

#include "macro.h"
#include "vector.h"
#include "piece.h"

typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

// encapsulated
static int  find_index (board*, vec2);
static void move_piece (board*, piece, vec2);

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
	b->nb_pieces = MAX_PIECES;
	b->prevLong  = NULL;

	return b;
}

board * clone(board * b) {

	// copy content of board into an new one
	board * c = malloc(sizeof(board));
	for (int i=0; i < b->nb_pieces; ++i) {
		c->pieces[i] = b->pieces[i];
	}
	c->nb_pieces = b->nb_pieces;
	c->prevLong  = NULL;
	return c;
}

char valid (vec2 p) {
	return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
}

piece find (board * b, vec2 p) {
	int i = find_index(b, p);
	if (i < 0) return no_piece(); // failed to find
	return b->pieces[i];
}

char remove (board * b, vec2 p) {
	int i = find_index(b, p);
	if (i < 0) return NO; // failed to remove

	// take last piece and overwrite at index found and reduce array size
	b->pieces[i] = b->pieces[--b->nb_pieces];
	return YES;
}

void move_ (board * b, piece p, move m) {
	// remove target
	remove(b, m.target.pos);

	// move current piece
	move_piece(b, p, m.dest);
	free(b->prevLong); // delete previous long move

	// if long move, store info in the board
	if (m.isLong)
		b->prevLong = make_holder(m.dest, p);

	// if castling
	else if (m.ext != NULL) {
		move e = *(m.ext);
		move_piece(b, e.target, e.dest);
	}
}

int get_moves (board * b, char t, vec2 p, vec2 o[NB_CELLS]) {
	int i = find_index(b, p);
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


static int find_index (board * b, vec2 p) {
	for (int i = 0; i < b->nb_pieces; ++i) {
		if (equ(b->pieces[i].pos, p))
			return i;
	}
	return -1; // failed to find
}

static void move_piece (board * b, piece p, vec2 d) {
	int i = find_index(b, p);
	if (i < 0) return;

	p.pos      = d;
	p.hasMoved = YES;
	b->pieces[i] = p;
}


char move_pos (board * b, vec2 p, vec2 d) {
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
}
