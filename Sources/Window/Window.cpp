#include "Window.hpp"

bool Window::has_instance = false;

Window::Window()
{
	
}

Window & Window::create(WindowMode window_mode, Vec2i resolution)
{
	static Window window = Window(window_mode, resolution);
	Window::has_instance = true;

	return window;
}

Window::Window(WindowMode window_mode, Vec2i resolution)
{
	sdl_window = SDL_CreateWindow("Engine", 0, 0, resolution.x, resolution.y, window_mode);
}

Window::~Window()
{
	SDL_DestroyWindow(sdl_window);
}