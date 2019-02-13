/*
 * Author: olivier
 */

#include "board.h"

#include "macro.h"
#include "vector.h"
#include "piece.h"
#include "move.h"

typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

// encapsulated
static int  find_index     (board*, vec2);
static void displace_piece (board*, piece, vec2);

board * make_board () {

	// create a new board that will survive
	// out of the scope of this function
	board * board = malloc(sizeof(struct board));

	// order of pieces
	int o[] = {ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK};

	// fill both row with pawns
	for (int i = 0, j = 0; i < 8; ++i) {
		board->pieces[j++] = make_piece(i,0,WHITE,o[i]);
		board->pieces[j++] = make_piece(i,1,WHITE,PAWN);
		board->pieces[j++] = make_piece(i,6,BLACK,PAWN);
		board->pieces[j++] = make_piece(i,7,BLACK,o[i]);
	}
	board->nb_pieces  = MAX_PIECES;
	board->pos_jumped = null_vector();
	board->prev_pawn  = null_piece ();
	return board;
}

board * clone_board (board * board0) {

	// copy content of board into an new one
	board * board1 = malloc(sizeof(board));
	for (int i=0; i < board0->nb_pieces; ++i) {
		board1->pieces[i] = board0->pieces[i];
	}
	board1->nb_pieces  = board0->nb_pieces;
	board1->pos_jumped = board0->pos_jumped;
	board1->prev_pawn  = board0->prev_pawn;
	return board1;
}

piece find (board * board, vec2 pos) {
	int i = find_index(board, pos);
	if (i < 0) return null_piece(); // failed to find
	return board->pieces[i];
}

char is_valid (vec2 pos) {
	return
		0 <= pos.x && pos.x < 8 &&
		0 <= pos.y && pos.y < 8;
}

char remove_piece (board * board, vec2 pos) {
	int i = find_index(board, pos);
	if (i < 0) return NO; // failed to remove

	// take last piece and overwrite at index found and reduce array size
	board->pieces[i] = board->pieces[ --board->nb_pieces ];
	return YES;
}

void move_piece (board * board, piece piece, move move) {
	// remove target
	remove_piece(board, move.target.pos);

	// move current piece
	displace_piece(board, piece, move.dest);

	// if long move, store info in the board
	if (move.isLong) {
		board->pos_jumped = move.dest;
		board->prev_pawn  = piece;
	} else {
		board->pos_jumped = null_vector();
		board->prev_pawn  = null_piece ();
	}
	// if castling
	if (move.ext != NIL) {
		displace_piece(board, move.ext->target, move.ext->dest);
	}
}


/*
 * to draw the board:
 * top:  8 , bottom: 1
 * left: A , right:  H
 * */
void draw_board (board * board) {
	vec2 pos = make_vector(0, 0);

	// display labels around the board
	printf("  A B C D E F G H  \n");
	for (pos.y = 7; pos.y >= 0; --pos.y) {
		printf("%d " , pos.y + 1);
		for (pos.x = 0; pos.x < 8; ++pos.x) {

			// get the piece at the specified location
			piece piece = find(board, pos);
			if (is_null_piece(piece)) { // draw an empty cell
				if (is_even(pos)) printf(". ");
				else              printf("  ");
			}
			// print a piece
			else {
				if (piece.team) printf(ANSI_CYAN);
				else            printf(ANSI_YELLOW);
				printf("%c " ANSI_RESET, get_visual(piece));
			}
		}
		printf("%d\n", pos.y + 1);
	}
	printf("  A B C D E F G H  \n");
}

char was_long_move (struct board * board) {
	return
		! is_null_vector(board->pos_jumped) &&
		! is_null_piece (board->prev_pawn );
}



/* PRIVATE FUNCTIONS */

static int find_index (board * board, vec2 pos) {
	for (int i = 0; i < board->nb_pieces; ++i) {
		if (equ(board->pieces[i].pos, pos))
			return i;
	}
	return -1; // failed to find
}

static void displace_piece (board * board, piece piece, vec2 dest) {
	int i = find_index(board, dest);
	if (i < 0) return;

	piece.pos      = dest;
	piece.hasMoved = YES;
	board->pieces[i] = piece;
}

