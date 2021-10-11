#pragma once

#include <SDL.h>

enum WindowDisplayType
{
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	EXCLUSIVE_FULLSCREEN = SDL_WINDOW_FULLSCREEN_DESKTOP,
	WINDOWED = 0
};

class Window
{
public:
	char title[256];
	int x;
	int y;
	int w;
	int h;
	WindowDisplayType window_display_type;
	
	Window(char title[], int x, int y, int w, int h, WindowDisplayType window_display_type);
};