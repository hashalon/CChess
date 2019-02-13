/*
 * Author: olivier
 */

#ifndef BOARD_H_
#define BOARD_H_

#define MAX_PIECES 32
#define NB_CELLS   64

#include "vector.h"
#include "piece.h"
#include "move.h"

struct board {
	char          nb_pieces;
	struct piece  pieces[MAX_PIECES];
	struct vec2   pos_jumped; // store position that was jumped by long move
	struct piece  prev_pawn;  // pawn that performed the long move
};

// create an initial board with pieces
struct board * make_board ();

// clone the board so that it is possible to do tests on it
struct board * clone_board (struct board*);

// find piece at given location
struct piece find (struct board*, struct vec2);

// see if the position is within the boundaries of a chess board
char is_valid (struct vec2);

// remove piece at given location
char remove_piece (struct board*, struct vec2);

// apply move data to piece
void move_piece (struct board*, struct piece, struct move);

// draw the board to the console
void draw_board (struct board*);


// manage previous move for pawns' en passant
char was_long_move (struct board*);


#endif /* BOARD_H_ */
