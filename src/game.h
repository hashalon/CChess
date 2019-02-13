/*
 * Author: olivier
 */

#ifndef GAME_H_
#define GAME_H_

// define the state of the game
#define NEXT_TURN  0
#define CHECK_MATE 1

// define return code of 'play_turn' function
// allow to display an appropriate error message
#define SUCCESS      0 // valid move
#define OUT_OF_BOUND 1 // selection out of the boundaries of the board
#define NO_PIECE     2 // no piece selected
#define ENEMY_PIECE  3 // enemy piece selected
#define INVALID_MOVE 4 // selected piece cannot perform move
#define SELF_CHECK   5 // move would put our king in check

#define PLAYER_WHITE "Player White"
#define PLAYER_BLACK "Player Black"

#include "vector.h"

struct board;

// draw a turn of the game
char draw_turn (struct board*, char);

// play a turn of the game
char play_turn (struct board*, char, struct vec2, struct vec2);

// see if the player is in check
char test_for_check (struct board*, char);

#endif /* GAME_H_ */
