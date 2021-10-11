#pragma once

#include <SDL.h>

enum class Type
{
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	EXCLUSIVE_FULLSCREEN = SDL_WINDOW_DESKTOP
};

class Window;