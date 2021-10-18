
#define SDL_MAIN_HANDLED
#include <cstdlib>

#include "Engine/Engine.hpp"

int main()
{
	Engine engine = Engine::create();

	while (engine.is_running)
	{
		engine.process_events();
	}

	return EXIT_SUCCESS;
}