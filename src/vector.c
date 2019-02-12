#include "vector.h"

// type definitions
typedef struct vec2 vec2;

vec2 make_vector (int x, int y) {
	vec2 o = {x, y}; return o;
}

vec2 inv (vec2 v) {
	vec2 o = {-v.x, -v.y}; return o;
}
vec2 add (vec2 u, vec2 v) {
	vec2 o = {u.x + v.x, u.y + v.y}; return o;
}
vec2 mul (vec2 v, char s) {
	vec2 o = {v.x * s, v.y * s}; return o;
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

vec2 null_vector () {
	vec2 o = {-128, -128}; return o;
}
char is_null_vector(vec2 v) {
	return v.x == -128 && v.y == -128;
}
