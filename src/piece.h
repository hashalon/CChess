/*
 * Author: olivier
 */

#ifndef PIECE_H_
#define PIECE_H_

#define WHITE 0
#define BLACK 1

#define PAWN   0
#define ROOK   1
#define KNIGHT 2
#define BISHOP 3
#define QUEEN  4
#define KING   5


#include "vector.h"
struct move;
struct board;

// data of a piece
struct piece {
	struct vec2 pos;
	char team, type, hasMoved;
};

// helper to build a piece
struct piece make_piece (int,int,int,int);

// get possible moves for the given piece
int get_moves (struct board*, struct piece, struct move*);

// invalid piece are used to specify that
// no piece was found at a given location
struct piece null_piece ();
char is_null_piece(struct piece);

char get_visual(struct piece);

#endif /* PIECE_H_ */
