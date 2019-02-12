#ifndef MOVE_H_
#define MOVE_H_

#include "vector.h"
#include "piece.h"

struct move {
	struct vec2   dest;   // destination of the move
	struct piece  target; // piece attacked
	struct move * ext;    // may be null
	char          isLong; // tells if is is a long move
};


// helpers to create the different types of move
struct move make_move     (struct vec2, struct piece);
struct move make_longmove (struct vec2);
struct move make_castling (struct vec2, struct vec2, struct piece);

// generate a data holder to store in the "prev_long" variable of a board
struct move make_holder (struct vec2, struct piece);
struct move null_holder ();

// check if anything has been stored in "prev_long"
char is_null_holder (struct move);

// to delete a move properly, we have to free the "ext" pointer
void del_move (struct move);

#endif /* MOVE_H_ */
