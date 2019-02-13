/*
 * Author: olivier
 */

#include "move.h"

#include "macro.h"
#include "vector.h"
#include "piece.h"
#include "board.h"

// type definitions
typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

move make_move (vec2 dest, piece attacked) {
	move move = {dest, attacked, NIL, NO};
	return move;
}
move make_longmove (vec2 dest) {
	move move = {dest, null_piece(), NIL, YES};
	return move;
}
move make_castling (vec2 dest1, vec2 dest2, piece rook) {
	move
		 c0 = {dest2, rook, NIL, NO},
		*c1 = malloc(sizeof(move));
	*c1 = c0;

	move move = {dest1, null_piece(), c1, NO};
	return move;
}

move null_move () {
	move move = {null_vector(), null_piece(), NIL, NO};
	return move;
}

char is_null_move (move move) {
	return
			is_null_vector(move.dest) ||
			is_null_piece (move.target);
}

move * make_move_set() {
	move * moves = malloc(NB_CELLS * sizeof(move));
	return moves;
}

void delete_moveset (move * moves) {
	// free the "ext" pointer of each entry
	for (int i=0; i < NB_CELLS; ++i)
		free(moves[i].ext);
	free(moves);
}
