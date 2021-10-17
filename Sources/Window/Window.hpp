#pragma once

#include "Utilities/Vector2.hpp"

#include <SDL2/SDL_render.h>

#include <string>

enum WindowMode
{
	BORDERLESS = SDL_WINDOW_FULLSCREEN_DESKTOP,
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	WINDOWED = 0
};

class Window
{
public:
	static Window & create(WindowMode window_mode, Vec2i resolution);
	~Window();
	SDL_Window *sdl_window;
	Window();

private:
	SDL_Renderer *sdl_renderer;
	static bool has_instance;
	
	Window(WindowMode window_mode, Vec2i resolution);
};