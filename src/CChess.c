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

typedef struct vec2  vec2;
typedef struct piece piece;
typedef struct move  move;
typedef struct board board;

int main(void) {
	// start with white and prepare a new board
	char    team  = WHITE;
	board * board = make_board();
	printf("start the game\n");

	// clear the board
	free(board);
	printf("finish the game\n");
	return EXIT_SUCCESS;
}
