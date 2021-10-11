#include <cstdlib>

#include "Engine.hpp"

Engine::Engine(const Window& window)
{
	
	
	sdl_window = SDL_CreateWindow(window.title.c_str(), window.x, window.y, window.w, window.h, window.window_display_type);
}
	
Engine::~Engine()
{
	SDL_Quit();
}