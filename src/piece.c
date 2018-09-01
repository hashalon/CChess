#include "piece.h"

#include "vector.h"
#include "board.h"

#define D4 4
#define D8 8
#define SET 64

vec2 D_orth[D4] = {{ 1, 0}, { 0, 1}, {-1, 0}, { 0,-1}};
vec2 D_diag[D4] = {{ 1, 1}, {-1, 1}, {-1,-1}, { 1,-1}};
vec2 D_jump[D8] = {{ 2, 1}, {-2, 1}, {-2,-1}, { 2,-1},
                      { 1, 2}, {-1, 2}, {-1,-2}, { 1,-2}};

piece make_piece (int x, int y, int team, int type) {
	piece p = {vector(x,y), team, type};
	return p;
}

int moves_pawn   (board*b, piece p, vec2 o[SET]) {

	// TODO ...
	return 0;
}
int moves_rook   (board*b, piece p, vec2 o[SET]) {
	return moves_rider (b, p.pos, p.team, D4, D_orth, 0, o);
}
int moves_knight (board*b, piece p, vec2 o[SET]) {
	return moves_leaper(b, p.pos, p.team, D8, D_jump, 0, o);
}
int moves_bishop (board*b, piece p, vec2 o[SET]) {
	return moves_rider (b, p.pos, p.team, D4, D_diag, 0, o);
}
int moves_queen  (board*b, piece p, vec2 o[SET]) {
	int s = 0;
	s = moves_rider (b, p.pos, p.team, D4, D_orth, s, o);
	s = moves_rider (b, p.pos, p.team, D4, D_diag, s, o);
	return s;
}
int moves_king   (board*b, piece p, vec2 o[SET]) {
	int s = 0;
	s = moves_leaper(b, p.pos, p.team, D4, D_orth, s, o);
	s = moves_leaper(b, p.pos, p.team, D4, D_diag, s, o);

	// check for castling...
	// TODO ...

	return s;
}

int moves_leaper (board*b, vec2 p, char t, int sd, vec2 d[D8], int so, vec2 o[SET]) {
	// TODO ...
	return so;
}
int moves_rider  (board*b, vec2 p, char t, int sd, vec2 d[D8], int so, vec2 o[SET]) {
	// TODO ...
	return so;
}

piece invalid_piece () {
	piece p = {invalid_vector(), -1, -1};
	return p;
}
