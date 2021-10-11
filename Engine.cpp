#include <cstdlib>

#include "Engine.hpp"

Engine::Engine(const Window& window)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	sdl_window = SDL_CreateWindow(window.title, window.x, window.y, window.w, window.h, window.window_display_type);
}
	
Engine::~Engine()
{
	SDL_Quit();
}