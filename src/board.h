#ifndef BOARD_H_
#define BOARD_H_

#define SIZE        8
#define MAX_PIECES 32
#define NB_CELLS   64

typedef struct vec2  vec2;
typedef struct piece piece;

typedef struct board {
	char nb_pieces;
	piece pieces[MAX_PIECES];
} board;

board* make_board ();

char valid  (vec2);

int  find   (board*, vec2);
char remove (board*, vec2);
char move   (board*, vec2, vec2);

int get_moves (board*, char, vec2, vec2[]);

#endif /* BOARD_H_ */
