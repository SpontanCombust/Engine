#include <cstdlib>

#include "Engine.hpp"

Engine *Engine::instance = nullptr;

void Engine::create( const Window& window ) 
{
	is_running = false;
}

void Engine::start() 
{
	is_running = true;
	while( is_running )
	{
		
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