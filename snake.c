#include "snake.h"
#include "game.h"

void move(snake_t *snake, SDL_Rect *fillRect, SDL_Renderer *renderer)
{
  fillRect->x = snake->x;
  fillRect->y = snake->y;
  
  for (int i = 0; i < snake->length; i++) {
    SDL_RenderFillRect(renderer, fillRect);
    switch (snake->direction)
      {
      case UP:
	fillRect->y += SIZE;
	break;	
      case DOWN:
	fillRect->y -= SIZE;
	break;
      case LEFT:
	fillRect->x += SIZE;
	break;
      case RIGHT:
	fillRect->x -= SIZE;
	break;
      }
  }

  if (snake->x % SCREEN_WIDTH == 0 || snake->y % SCREEN_HEIGHT == 0)
    snake->dead = true;
}
