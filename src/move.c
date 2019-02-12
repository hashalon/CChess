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
	move move = {dest, attacked, NULL, NO};
	return move;
}
move make_longmove (vec2 dest) {
	move move = {dest, null_piece(), NULL, YES};
	return move;
}
move make_castling (vec2 dest1, vec2 dest2, piece rook) {
	move
		 c0 = {dest2, rook, NULL, NO},
		*c1 = malloc(sizeof(move));
	*c1 = c0;

	move move = {dest1, null_piece(), c1, NO};
	return move;
}

// generate a holder for board's "prev_long"
move make_holder (vec2 dest, piece pawn) {
	if (pawn.team) ++dest.y;
	else           --dest.y;

	move holder = {dest, pawn, NULL, YES};
	return holder;
}

move null_holder () {
	move holder = {null_vector(), null_piece(), NULL, NO};
	return holder;
}

char is_null_holder (move holder) {
	return
		is_null_vector(holder.dest  ) ||
		is_null_piece (holder.target);
}

void del_move (move move) {
	free(move.ext);
}
