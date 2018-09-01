#include "vector.h"

vec2 vector (int x, int y) {
	vec2 r = {x, y}; return r;
}

vec2 inv (vec2 v) {
	vec2 r = {-v.x, -v.y}; return r;
}
vec2 add (vec2 u, vec2 v) {
	vec2 r = {u.x + v.x, u.y + v.y}; return r;
}
vec2 mul (vec2 v, char s) {
	vec2 r = {v.x * s, v.y * s}; return r;
}
vec2 rot (vec2 v, char r) {
	r = ((r % 4) + 4) % 4;
	vec2 o;
	switch (r) {
	case 1:  o.x = -v.y; o.y =  v.x; break;
	case 2:  o.x = -v.x; o.y = -v.y; break;
	case 3:  o.x =  v.y; o.y = -v.x; break;
	default: o.x =  v.x; o.y =  v.y; break;
	}
	return o;
}
char equ (vec2 u, vec2 v) {
	return u.x == v.x && u.y == v.y;
}

/*ID id (vec2 v) {
	ID x = v.x, y = v.y;
	return x | (y << 8);
}*/

vec2 invalid_vector () {
	vec2 r = {-128, -128}; return r;
}
