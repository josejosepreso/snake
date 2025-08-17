#include <stdlib.h>
#include <math.h>
#include "snake.h"
#include "game.h"

int thing_x;
int thing_y;

bool collides(const snake_t *snake) {
	point_t *points = snake->positions;

	for (int i = 0; i < snake->length; ++i)
		for (int j = i + 1; j < snake->length; ++j)
				if (points[i].x == points[j].x && points[i].y == points[j].y)
					return true;
	return false;
}

void move_snake(snake_t *snake)
{
	int x = snake->positions[0].x, y = snake->positions[0].y, nx, ny;

	if (x % (GAME_WIDTH - SIZE) == 0 || y % (GAME_HEIGHT - SIZE) == 0 || collides(snake))
		{
			snake->dead = true;
			return;
		}

	if (x == thing_x && y == thing_y)
		{
			snake->length++;
			snake->positions = realloc(snake->positions, sizeof(point_t) * (snake->length + 1));

			thing_x = floor(rand() % GAME_WIDTH / 10) * 10;
			thing_y = floor(rand() % GAME_HEIGHT / 10) * 10;
		}

	switch (snake->direction)
		{
		case UP:
			snake->positions[0].y -= SIZE;
			break;
		case DOWN:
			snake->positions[0].y += SIZE;
			break;
		case LEFT:
			snake->positions[0].x -= SIZE;
			break;
		case RIGHT:
			snake->positions[0].x += SIZE;
			break;
		}

	for (int i = 1; i < snake->length; ++i)
		{
			nx = snake->positions[i].x;
			ny = snake->positions[i].y;

			snake->positions[i].x = x;
			snake->positions[i].y = y;

			x = nx;
			y = ny;
		}
}
