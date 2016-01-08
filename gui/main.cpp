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
#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 512

SDL_Window *mainWindow;

void sdl_create_window ()
{
	mainWindow = SDL_CreateWindow (WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_ALLOW_HIGHDPI);
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
