#include <SDL2/SDL.h>
#include <stdbool.h>
#include "game.h"
#include "snake.h"
#include "rendering.h"

int main(void)
{
  SDL_Window *window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return EXIT_FAILURE;

	window = SDL_CreateWindow("snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window)
		return EXIT_FAILURE;

	SDL_SetWindowResizable(window, false);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int initialHPos = SCREEN_WIDTH / 3;
	int initialVPos = SCREEN_HEIGHT / 3;

	SDL_Rect fillRect = { initialHPos, initialVPos, SIZE, SIZE };

	point_t *positions = malloc(sizeof(point_t) * INITIAL_LENGTH);
	for (int i = 0; i < INITIAL_LENGTH; ++i)
		positions[i] = (point_t) { INITIAL_LENGTH + initialHPos - (i - 1) * SIZE, initialVPos };

	snake_t snake = { positions, RIGHT, INITIAL_LENGTH, false };

	thing_x = floor(rand() % GAME_WIDTH / 10) * 10;
	thing_y = floor(rand() % GAME_HEIGHT / 10) * 10;

	bool quit = false;
	SDL_Event e;

	while (!quit)
		{
			while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = true;

					switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							if (snake.direction != UP && snake.direction != DOWN)
								snake.direction = UP;
							break;
						case SDLK_DOWN:
							if (snake.direction != UP && snake.direction != DOWN)
								snake.direction = DOWN;
							break;
						case SDLK_LEFT:
							if (snake.direction != RIGHT && snake.direction != LEFT)
								snake.direction = LEFT;
							break;
						case SDLK_RIGHT:
							if (snake.direction != RIGHT && snake.direction != LEFT)
								snake.direction = RIGHT;
							break;
						default:
							break;
						}
				}

			if (snake.dead)
				continue;

			move_snake(&snake);

			render_game(&snake, renderer, &fillRect);

			SDL_RenderPresent(renderer);
			SDL_Delay(32);
	}

	free(snake.positions);

	return 0;
}
