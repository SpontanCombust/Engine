#include "Window.hpp"


Window::Window() 
{
	sdl_window = nullptr;
	sdl_renderer = nullptr;
}

Window::Window(const char *title, int x, int y, int w, int h, WindowDisplayType window_display_type)
{
	sdl_window = SDL_CreateWindow( title, x, y, w, h, window_display_type );
	sdl_renderer = SDL_CreateRenderer( sdl_window, -1, SDL_RENDERER_ACCELERATED );
}

vec2i Window::get_position() const
{
	vec2i pos;
	SDL_GetWindowPosition( sdl_window, &pos.x, &pos.y );
	return pos;
}

vec2i Window::get_size() const
{
	vec2i size;
	SDL_GetWindowSize( sdl_window, &size.x, &size.y );
	return size;
}

WindowDisplayType Window::get_display_type() const
{
	return WINDOWED; //TODO
}

void Window::clear() 
{
	SDL_RenderClear( sdl_renderer );
}

void Window::draw() 
{
	SDL_RenderPresent( sdl_renderer );
}
