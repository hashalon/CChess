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

typedef struct vec2  vec2;
typedef struct board board;

typedef struct piece {
	vec2 pos;
	char team, type;
} piece;

piece make_piece (int,int,int,int);

// movement functions (return arrays)
int moves_pawn   (board*, piece, vec2[]);
int moves_rook   (board*, piece, vec2[]);
int moves_knight (board*, piece, vec2[]);
int moves_bishop (board*, piece, vec2[]);
int moves_queen  (board*, piece, vec2[]);
int moves_king   (board*, piece, vec2[]);

int moves_leaper (board*, vec2, char, int, vec2[], int, vec2[]);
int moves_rider  (board*, vec2, char, int, vec2[], int, vec2[]);

piece invalid_piece ();

#endif /* PIECE_H_ */
