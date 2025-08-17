#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 630

#define GAME_WIDTH 810
#define GAME_HEIGHT 600

#define SIZE 10
#define INITIAL_LENGTH 10

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
	bool dead;
} snake_t;

int thing_x;
int thing_y;

void move(snake_t *);

bool collides(const point_t *, const int);

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

			move(&snake);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

			SDL_RenderDrawLine(renderer, 0, 0, GAME_WIDTH, 0);
			SDL_RenderDrawLine(renderer, GAME_WIDTH, 0, GAME_WIDTH, GAME_HEIGHT);
			SDL_RenderDrawLine(renderer, GAME_WIDTH, GAME_HEIGHT, 0, GAME_HEIGHT);
			SDL_RenderDrawLine(renderer, 0, GAME_HEIGHT, 0, 0);

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);

			fillRect.x = thing_x;
			fillRect.y = thing_y;

			SDL_RenderFillRect(renderer, &fillRect);

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

			for (int i = 0; i < snake.length; ++i)
				{
					fillRect.x = snake.positions[i].x;
					fillRect.y = snake.positions[i].y;

					SDL_RenderFillRect(renderer, &fillRect);
				}

			SDL_RenderPresent(renderer);
			SDL_Delay(32);
	}

	free(snake.positions);

	return 0;
}

void move(snake_t *snake)
{
	int x = snake->positions[0].x, y = snake->positions[0].y, nx, ny;

	if (x % GAME_WIDTH == 0
			|| y % GAME_HEIGHT == 0
			|| collides(snake->positions, snake->length))
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

bool collides(const point_t *points, const int size) {
	for (int i = 0; i < size; ++i)
		for (int j = i + 1; j < size; ++j)
				if (points[i].x == points[j].x
						&& points[i].y == points[j].y)
					return true;
	return false;
}
