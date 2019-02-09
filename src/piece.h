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

struct piece {
	struct vec2 pos;
	char team, type, hasMoved;
};

struct piece make_piece (int,int,int,int);

// movement functions (return arrays)
int moves_pawn   (struct board*, struct piece, struct move*);
int moves_rook   (struct board*, struct piece, struct move*);
int moves_knight (struct board*, struct piece, struct move*);
int moves_bishop (struct board*, struct piece, struct move*);
int moves_queen  (struct board*, struct piece, struct move*);
int moves_king   (struct board*, struct piece, struct move*);

struct piece no_piece ();
char is_free_piece(struct piece);

#endif /* PIECE_H_ */
