#pragma once

#include <SDL.h>

#include "Window.hpp"

class Engine
{
public:
	SDL_Window *sdl_window;

	Engine(const Window& window);
	
	~Engine();
};