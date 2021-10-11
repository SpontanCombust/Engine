#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "Window.hpp"

class Engine
{
public:

	void create( const Window& window );

	void start();

	void exit();

	static Engine *getInstance();

private:
	static Engine *instance;
	bool is_running;
};