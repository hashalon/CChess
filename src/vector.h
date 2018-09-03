#ifndef VECTOR_H_
#define VECTOR_H_

// vec2 position or direction in 2D board
struct vec2 {
	char x, y;
};

//typedef unsigned short ID;

struct vec2 vector (int, int);

struct vec2 inv (struct vec2);
struct vec2 add (struct vec2, struct vec2);
struct vec2 mul (struct vec2, char);
struct vec2 rot (struct vec2, char);
char        equ (struct vec2, struct vec2);

//ID id (vec2);

struct vec2 invalid_vector ();
char is_free(struct vec2);

#endif /* VECTOR_H_ */
