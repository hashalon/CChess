/*
 * Author: olivier
 */

#ifndef VECTOR_H_
#define VECTOR_H_

// vec2 position or direction in 2D board
struct vec2 {
	char x, y;
};

struct vec2 make_vector (int, int);

struct vec2 inv (struct vec2);
struct vec2 add (struct vec2, struct vec2);
struct vec2 mul (struct vec2, char);
struct vec2 rot (struct vec2, char);
char        equ (struct vec2, struct vec2);

struct vec2 null_vector ();
char is_null_vector(struct vec2);

char is_even (struct vec2);

#endif /* VECTOR_H_ */
