#include <SDL2/SDL.h>
#include "snake.h"
#include "game.h"

void render_snake(snake_t *snake, SDL_Renderer *renderer, SDL_Rect *fillRect)
{
	fillRect->x = snake->positions[0].x;
	fillRect->y = snake->positions[0].y;
	SDL_RenderFillRect(renderer, fillRect);
	SDL_RenderFillRect(renderer, fillRect);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (int i = 1; i < snake->length; ++i)
		{
			fillRect->x = snake->positions[i].x;
			fillRect->y = snake->positions[i].y;

			SDL_RenderFillRect(renderer, fillRect);
		}
}

void render_borders(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderDrawLine(renderer, 0, 0, GAME_WIDTH, 0);
	SDL_RenderDrawLine(renderer, GAME_WIDTH, 0, GAME_WIDTH, GAME_HEIGHT);
	SDL_RenderDrawLine(renderer, GAME_WIDTH, GAME_HEIGHT, 0, GAME_HEIGHT);
	SDL_RenderDrawLine(renderer, 0, GAME_HEIGHT, 0, 0);
}

void render_thing(SDL_Renderer *renderer, SDL_Rect *fillRect)
{
	fillRect->x = thing_x;
	fillRect->y = thing_y;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	SDL_RenderFillRect(renderer, fillRect);
}

void render_game(snake_t *snake, SDL_Renderer *renderer, SDL_Rect *fillRect)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	render_thing(renderer, fillRect);

	render_borders(renderer);

	render_snake(snake, renderer, fillRect);
}
