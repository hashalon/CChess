/*
 * Author: olivier
 */

#include "game.h"

#include <stdio.h>

#include "macro.h"
#include "vector.h"
#include "piece.h"
#include "move.h"
#include "board.h"

typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

// helper functions
static vec2 parse_input   (char, char);
static move is_part_of_set(move*, int, vec2);
static char is_king_in_set(move*, int, char);

/* PUBLIC FUNCTIONS */

// draw the board, and ask the player for input,
// display error messages, return once the turn is over
char draw_turn (board * board, char player) {
	// draw current state of the board
	printf("\n");
	draw_board(board);
	printf("\n");

	// ask the player for a valid input
	char valid = NO;
	char input[6]; // inputs with the format: "A1 B2"
	while (!valid) {
		// ask the player to enter a move
		if (player) printf(ANSI_CYAN   PLAYER_BLACK ", please make a move: " ANSI_RESET);
		else        printf(ANSI_YELLOW PLAYER_WHITE ", please make a move: " ANSI_RESET);

		// get data from player input (ignore spaces)
		fread(input, 6, 1, stdin);
		vec2
			select = parse_input(input[0], input[1]),
			dest   = parse_input(input[3], input[4]);
		char error = play_turn(board, player, select, dest);

		// display error message on failure
		switch (error) {
		case SUCCESS:      valid = YES; break;
		case OUT_OF_BOUND: printf(ANSI_RED "Move is out of bound.\n"          ANSI_RESET); break;
		case NO_PIECE:     printf(ANSI_RED "Selected an empty cell.\n"        ANSI_RESET); break;
		case ENEMY_PIECE:  printf(ANSI_RED "Selected an enemy piece.\n"       ANSI_RESET); break;
		case INVALID_MOVE: printf(ANSI_RED "The piece cannot do this move.\n" ANSI_RESET); break;
		case SELF_CHECK:   printf(ANSI_RED "Move would put king in check.\n"  ANSI_RESET); break;
		}
	}
	printf("\n");

	// TODO: detect checkmate state
	return NEXT_TURN;
}

// try to perform move, return appropriate error code otherwise
char play_turn (board * board, char player, vec2 select, vec2 dest) {
	// we must always be within the boundaries of the board
	// (the input system should make this error impossible)
	if (!is_valid(select) || !is_valid(dest)) return OUT_OF_BOUND;

	// get piece to move
	piece piece = find(board, select);

	// empty cell selected or enemy piece
	if      (is_null_piece(piece)) return NO_PIECE;
	else if (piece.team != player) return ENEMY_PIECE;

	// get the set of moves permitted for this piece and this turn
	// if the destination is part of the set, apply it
	move * moves = make_move_set();
	int    size  = get_moves(board, piece, moves);

	// check if the selected move is part of the set
	move move = is_part_of_set(moves, size, dest);
	delete_moveset(moves); // (we are done with the moveset)
	if (is_null_move(move)) return INVALID_MOVE;

	// see if selected move will lead to a self check
	struct board * board0 = clone_board (board);
	move_piece(board0, piece, move); // apply the move on the copy
	if (test_for_check(board0, player)) return SELF_CHECK;

	// move can be applied !
	move_piece(board, piece, move);
	return SUCCESS;
}

// return true if the player is in check
char test_for_check (board * board, char player) {
	// create a moveset once, reuse it for each piece
	move * moves = make_move_set();

	// Check each enemy piece.
	// If our king is a target of their moveset,
	// then we are in check
	for (int i = 0; i < board->nb_pieces; ++i) {
		// if the piece is not an enemy, try the next one
		piece enemy = board->pieces[i];
		if (enemy.team == player) continue;

		// fill the moveset
		int size = get_moves(board, enemy, moves);
		if (is_king_in_set(moves, size, player)) {
			delete_moveset(moves);
			return YES;
		}
	}

	// do not forget to delete the moveset
	delete_moveset(moves);
	return NO;
}

/* PRIVATE FUNCTIONS */

// get the corresponding position from the input
static vec2 parse_input (char col, char row) {
	int y;

	// input are directly input as characters
	if ('1' <= row && row <= '8') y = row - '1';
	else return null_vector();

	// we can use either lowercase or uppercase for letters
	if      ('A' <= col && col <= 'H') return make_vector(col - 'A', y);
	else if ('a' <= col && col <= 'h') return make_vector(col - 'a', y);
	else return null_vector();
}

// used to see if the given destination is part of the moveset
static move is_part_of_set (move * set, int size, vec2 dest) {
	// iterate through the moveset
	for (int i = 0; i < size; ++i) {

		// selected destination match the one found in the moveset
		move move = set[i];
		if (equ(move.dest, dest)) return move;
	}
	// no move found corresponding to destination
	return null_move();
}

// used to see if specified king is a target in the moveset
static char is_king_in_set(move * set, int size, char team) {
	// iterate through the moveset
	for (int i = 0; i < size; ++i) {
		// selected destination match the one found in the moveset
		piece target = set[i].target;
		if (
			target.team == team &&
			target.type == KING
		)
			return YES;
	}
	return NO;
}



