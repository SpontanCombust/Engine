#include "Engine/Engine.hpp"

#include <SDL2/SDL.h>

// #include "Logging/Logging.hpp" //TODO


Engine *Engine::instance = nullptr;

Engine* Engine::get_instance() 
{
	if( instance == nullptr )
	{
		instance = new Engine();
	}

	return instance;
}

Engine::Engine() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		exit(EXIT_FAILURE);
	}

	is_running = false;
}

Engine::~Engine() 
{
	SDL_Quit();
}

Window& Engine::create_window( const char *title, int w, int h, WindowMode window_mode ) 
{
	window = std::move( Window( title, w, h, window_mode ) );
	return window;
}

Window& Engine::get_window() 
{
	return window;
}

void Engine::process_events() 
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
				is_running = false;
				break;
			default:
				break;
		}
	}
}

void Engine::start() 
{
	is_running = true;

	while(is_running)
	{
		window.clear();

		process_events();

		window.flip_buffer();
	}
}

void Engine::stop() 
{
	is_running = false;
}