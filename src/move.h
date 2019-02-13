/*
 * Author: olivier
 */

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

struct move null_move();
char is_null_move(struct move);

// create an empty move set to fill
struct move* make_move_set();

// delete a whole move set
void delete_moveset (struct move*);

#endif /* MOVE_H_ */
