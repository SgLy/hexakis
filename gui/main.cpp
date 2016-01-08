#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>

void init_sdl ()
{
	if (SDL_VideoInit (NULL) < 0) {
		std::cerr << "Unable to initialize SDL video." << std::endl;
		std::exit (1);
	}
	atexit (SDL_VideoQuit);
}

#define WINDOW_TITLE "Hexakis"
#define BOARD_HEIGHT 40
#define BOARD_WIDTH 20
#define BOARD_TILE_SIZE 16

#define WINDOW_HEIGHT (BOARD_HEIGHT*BOARD_TILE_SIZE)
#define WINDOW_WIDTH (BOARD_WIDTH*BOARD_TILE_SIZE)

SDL_Window *mainWindow;

void sdl_create_window ()
{
	mainWindow = SDL_CreateWindow (WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!mainWindow) {
		std::cerr << "Unable to create main window." << std::endl;
		std::exit (2);
	}
	SDL_ShowWindow (mainWindow);
}

SDL_Surface *mainSurface;
SDL_Renderer *renderer;

void sdl_create_renderer ()
{
	mainSurface = SDL_GetWindowSurface (mainWindow);
	renderer = SDL_CreateSoftwareRenderer (mainSurface);
}

int main()
{
	init_sdl ();
	sdl_create_window ();
	SDL_Delay (1000);
	return 0;
}
