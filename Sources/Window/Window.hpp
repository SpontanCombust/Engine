#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

enum WindowMode
{
	BORDERLESS = SDL_WINDOW_FULLSCREEN_DESKTOP,
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	WINDOWED = 0
};

class Window
{
public:
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;

public:
	Window();
	Window( const char *title, int w, int h, WindowMode window_mode );
	~Window();

	Window& operator=( const Window& other );
	Window& operator=( Window&& other );

	void clear();
	void flip_buffer();

private:
	void destroy_if_valid();
};