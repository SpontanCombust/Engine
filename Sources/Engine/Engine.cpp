#include "Engine/Engine.hpp"

#include <SDL2/SDL.h>

#include "Logging/Logging.hpp"

bool Engine::has_instance = false;

Engine & Engine::create(WindowMode window_mode, Vec2i resolution, unsigned frame_rate, bool use_mouse, bool use_keyboard, bool log_to_console, bool log_to_file, std::string log_file_name)
{
	static Engine engine(window_mode, resolution, frame_rate, use_mouse, use_keyboard, log_to_console, log_to_file, log_file_name);
	Engine::has_instance = true;

	return engine;
}

void Engine::process_events()
{
	while (SDL_PollEvent(&sdl_event))
	{
		switch (sdl_event.window.event)
		{
			case SDL_WINDOWEVENT_CLOSE:
				Engine::is_running = false;
		}
	}
}

Engine::Engine(WindowMode window_mode, Vec2i resolution, unsigned frame_rate, bool use_mouse, bool use_keyboard, bool log_to_console, bool log_to_file, std::string log_file_name)
{
	if (!has_instance)
	{
		Logging logging = Logging::create(log_to_console, log_to_file, log_file_name);

		if (SDL_Init(SDL_INIT_EVERYTHING))
		{
			logging.log(std::string("Unable to initialize SDL: ") + std::string(SDL_GetError()));
			exit(EXIT_FAILURE);
		}

		window = Window::create(window_mode, resolution);

		primitive_renderer = PrimitiveRenderer::create(window);
	}
}

Engine::~Engine()
{
	SDL_Quit();
}