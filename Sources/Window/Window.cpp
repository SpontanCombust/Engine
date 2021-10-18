#include "Window.hpp"

#include "../Utilities/Log.hpp"

Window::Window() 
{
	sdl_window = nullptr;
	sdl_renderer = nullptr;
}

Window::Window(const char *title, int w, int h, WindowMode window_mode) 
{
	sdl_window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | window_mode );
	sdl_renderer = SDL_CreateRenderer( sdl_window, -1, SDL_RENDERER_ACCELERATED );
}

Window& Window::operator=(const Window& other) 
{
	destroy_if_valid();

	if(other.sdl_window)
	{
		const char *title = SDL_GetWindowTitle( other.sdl_window );
		int x, y;
		SDL_GetWindowPosition( other.sdl_window, &x, &y );
		int w, h;
		SDL_GetWindowSize( other.sdl_window, &w, &h );
		int win_flags = SDL_GetWindowFlags( other.sdl_window );

		SDL_RendererInfo render_info;
		SDL_GetRendererInfo( other.sdl_renderer, &render_info );
		

		sdl_window = SDL_CreateWindow( title, x, y, w, h, win_flags );
		sdl_renderer = SDL_CreateRenderer( sdl_window, -1, render_info.flags );
	}

	return *this;
}

Window& Window::operator=(Window&& other) 
{
	destroy_if_valid();

	sdl_window = other.sdl_window;
	sdl_renderer = other.sdl_renderer;

	other.sdl_window = nullptr;
	other.sdl_renderer = nullptr;

	return *this;
}

void Window::destroy_if_valid() 
{
	if(sdl_window)
	{
		SDL_DestroyRenderer(sdl_renderer);
		SDL_DestroyWindow(sdl_window);

		sdl_renderer = nullptr;
		sdl_window = nullptr;
	}
}

Window::~Window() 
{
	destroy_if_valid();
}

void Window::clear() 
{
	SDL_RenderClear(sdl_renderer);
}

void Window::flip_buffer() 
{
	SDL_RenderPresent(sdl_renderer);
}
