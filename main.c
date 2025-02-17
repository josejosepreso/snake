#include <SDL2/SDL.h>
#include <stdbool.h>
#include "snake.h"
#include "game.h"

int main(void)
{
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return EXIT_FAILURE;

  window = SDL_CreateWindow("snake",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);

  if (!window)
    return EXIT_FAILURE;

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Rect fillRect = { SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, SIZE, SIZE };
  
  snake_t snake = { fillRect.x, fillRect.y, RIGHT, INITIAL_LENGTH, false };

  int quit = 0;
  SDL_Event e;
  
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
	quit = 1;
      } else if (!snake.dead && e.type == SDL_KEYDOWN) {
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
    }

    if (snake.dead)
      continue;
    
    switch (snake.direction)
      {
      case UP:
	snake.y -= SPEED;
	break;	    
      case DOWN:
	snake.y += SPEED;
	break;
      case LEFT:
	snake.x -= SPEED;
	break;	    
      case RIGHT:
	snake.x += SPEED;
	break;
      default:
	break;
      }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);

    move(&snake, &fillRect, renderer);

    SDL_RenderPresent(renderer);
  }
  
  return 0;
}
