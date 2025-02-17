#ifndef SNAKE_H

#define SNAKE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

enum {
  LEFT,
  UP,
  DOWN,
  RIGHT
};

typedef struct {
  int x;
  int y;
  int direction;
  int length;
  bool dead;
} snake_t;

void move(snake_t *, SDL_Rect *, SDL_Renderer *);

#endif
