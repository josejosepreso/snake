#ifndef SNAKE_H

#define SNAKE_H

#include "game.h"

enum {
	LEFT,
	UP,
	DOWN,
	RIGHT
};

typedef struct {
	int x;
	int y;
} point_t;

typedef struct {
	point_t *positions;
	int direction;
	int length;
} snake_t;

void move_snake(snake_t *, game_t *);

#endif
