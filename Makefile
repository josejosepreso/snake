CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS = `pkg-config --libs sdl2`

snake: 	main.c
	$(CC) $(CFLAGS) -o snake main.c snake.c $(LIBS)
