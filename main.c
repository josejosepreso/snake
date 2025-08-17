#include <SDL2/SDL.h>
#include <stdbool.h>
#include "game.h"
#include "snake.h"
#include "rendering.h"

void init_game(snake_t *, game_t *);

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

	SDL_Rect fillRect = { 0, 0, SIZE, SIZE };

	game_t game = { 0 };
	snake_t snake = { 0 };
	init_game(&snake, &game);

	bool quit = false;
	SDL_Event e;

	while (!quit)
		{
			while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = true;

					if (game.state == DEAD) {
						if (e.key.keysym.sym == SDLK_SPACE)
							init_game(&snake, &game);
						break;
					}

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

			move_snake(&snake, &game);

			render_game(&snake, renderer, &fillRect);

			SDL_RenderPresent(renderer);
			SDL_Delay(32);
	}

	free(snake.positions);

	return 0;
}

void init_game(snake_t *snake, game_t *game)
{
	free(snake->positions);

	int initialHPos = GAME_WIDTH / 3;
	int initialVPos = GAME_HEIGHT / 3;

	point_t *positions = malloc(sizeof(point_t) * INITIAL_LENGTH);
	for (int i = 0; i < INITIAL_LENGTH; ++i)
		positions[i] = (point_t) { initialHPos - i * SIZE, initialVPos };

	snake->positions = positions;
	snake->direction = RIGHT;
	snake->length = INITIAL_LENGTH;

	thing_x = floor(rand() % GAME_WIDTH / 10) * 10;
	thing_y = floor(rand() % GAME_HEIGHT / 10) * 10;

	game->state = RUNNING;
	game->score = 0;
}
