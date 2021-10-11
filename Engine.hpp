#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "Window.hpp"

class Engine
{
public:
	static void create( const Window& window );

	static void start();

	static void exit();

	static Engine *getInstance();

private:
	static Window window;
	static Engine *instance;
	static bool is_running;
};