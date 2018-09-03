#ifndef BOARD_H_
#define BOARD_H_

#define SIZE        8
#define MAX_PIECES 32
#define NB_CELLS   64

struct vec2;
struct piece;
struct move;

struct board {
	char          nb_pieces;
	struct piece  pieces[MAX_PIECES];
	struct move * prevLong;
};

struct board * make_board ();
struct board * clone(struct board*);

char         valid     (struct vec2);
struct piece find      (struct board*, struct vec2);
char         remove    (struct board*, struct vec2);
void         move_     (struct board*, struct piece, struct move);
int          get_moves (struct board*, struct piece, struct move[]);

#endif /* BOARD_H_ */
