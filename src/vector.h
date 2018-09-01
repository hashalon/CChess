#ifndef VECTOR_H_
#define VECTOR_H_

// vec2 position or direction in 2D board
typedef struct vec2 {
	char x, y;
} vec2;

//typedef unsigned short ID;

vec2 vector (int, int);

vec2 inv (vec2);
vec2 add (vec2, vec2);
vec2 mul (vec2, char);
vec2 rot (vec2, char);
char equ (vec2, vec2);

//ID id (vec2);

vec2 invalid_vector ();

#endif /* VECTOR_H_ */
