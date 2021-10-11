#pragma once

#include <SDL.h>

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
	std::string title;
	int x;
	int y;
	int w;
	int h;
	WindowDisplayType window_display_type;
	
	Window(const char *title, int x, int y, int w, int h, WindowDisplayType window_display_type);
};