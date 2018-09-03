#include "move.h"

#include "macro.h"
#include "vector.h"
#include "piece.h"

// type definitions
typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

move make_move (vec2 dest, piece attacked) {
	move m = {dest, attacked, NULL, NO};
	return m;
}
move make_longmove (vec2 dest) {
	move m = {dest, no_piece(), NULL, YES};
	return m;
}
move make_castling (vec2 dest1, vec2 dest2, piece rook) {
	move
		 c0 = {dest2, rook, NULL, NO},
		*c1 = malloc(sizeof(move));
	*c1 = c0;

	move m = {dest1, no_piece(), c1, NO};
	return m;
}

// generate a holder for board's "prevLong"
move * make_holder (vec2 dest, piece pawn) {
	if (pawn.team) ++dest.y;
	else           --dest.y;

	move
		 h0 = {dest, pawn, NULL, YES},
		*h1 = malloc(sizeof(move));
	*h1 = h0;

	return h1;
}

//void delete_move (move m) {free(m.castling);}
