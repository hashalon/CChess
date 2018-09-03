#ifndef MOVE_H_
#define MOVE_H_

struct vec2;
struct piece;

struct move {
	struct vec2   dest;   // destination of the move
	struct piece  target; // piece attacked
	struct move * ext;    // may be null
	char          isLong; // tells if is is a long move
};


struct move make_move      (struct vec2, struct piece);
struct move make_longmove  (struct vec2);
struct move make_castling  (struct vec2, struct vec2, struct piece);

struct move * make_holder (struct vec2, struct piece);

//void delete_move (struct move);

#endif /* MOVE_H_ */
