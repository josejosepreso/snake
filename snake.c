#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "snake.h"
#include "game.h"

#include <stdio.h>

int thing_x;
int thing_y;

bool collides(const point_t *points, const int size) {
	int x = points[0].x, y = points[0].y;

	for (int i = 1; i < size; ++i)
		if (x == points[i].x && y == points[i].y)
			return true;
	return false;
}

void move_snake(snake_t *snake, game_t *game)
{
	int x = snake->positions[0].x, y = snake->positions[0].y, nx, ny;

	if (x % (GAME_WIDTH - SIZE) == 0 || y % (GAME_HEIGHT - SIZE) == 0 || collides(snake->positions, snake->length))
		{
			game->state = DEAD;
			return;
		}

	if (x == thing_x && y == thing_y)
		{
			game->score++;

			snake->length++;
			snake->positions = realloc(snake->positions, sizeof(point_t) * snake->length);

			thing_x = floor(rand() % GAME_WIDTH / 10) * 10;
			thing_y = floor(rand() % GAME_HEIGHT / 10) * 10;

			printf("%d\n", game->score);
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
