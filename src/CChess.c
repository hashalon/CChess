/*
 ============================================================================
 Name        : CChess.c
 Author      : Olivier Schyns
 Version     :
 Copyright   : MIT
 Description : Chess game made in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "macro.h"
#include "vector.h"
#include "piece.h"
#include "move.h"
#include "board.h"
#include "game.h"

typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

int main(void) {
	printf("=== CCHESS ===\n\n\n");

	// start with white and prepare a new board
	char player = WHITE, state = NEXT_TURN;
	board * board = make_board();

	while (state == NEXT_TURN) {
		state = draw_turn(board, player);
	}

	// clear the board
	free(board);
	return EXIT_SUCCESS;
}
