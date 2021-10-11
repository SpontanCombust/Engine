#pragma once

#include "Vector2.hpp"

#include <SDL2/SDL_render.h>

#include <string>

enum WindowDisplayType
{
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	EXCLUSIVE_FULLSCREEN = SDL_WINDOW_FULLSCREEN_DESKTOP,
	WINDOWED = 0
};

class Window
{
public:
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
	
	Window( const char *title, int x, int y, int w, int h, WindowDisplayType window_display_type );

	vec2i get_position() const;
	vec2i get_size() const;
	WindowDisplayType get_display_type() const;

	void clear();

	void draw();
};