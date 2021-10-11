#include <cstdlib>

#include "Engine.hpp"

Engine *Engine::instance = nullptr;
bool Engine::is_running = false;
Window Engine::window;

void Engine::create( const Window& _window ) 
{
	is_running = false;
	window = _window;
}

void Engine::start() 
{
	is_running = true;
	while( is_running )
	{
		// EVENTS //

		SDL_Event e;
		SDL_WaitEvent(&e);

		switch (e.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;
		}

		// LOGIC //

		

		// RENDERING //

		window.clear();

		

		window.draw();
	}
}

void Engine::exit() 
{
	is_running = false;
}

Engine *Engine::getInstance() 
{
	return instance;
}