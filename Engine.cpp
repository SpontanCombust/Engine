#include <cstdlib>

#inclue "Engine.hpp"

void screen_clear_callback()
{
	SDL_RenderClear();
}

class Engine
{
	Engine(const Window& window)
	{
		if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		{
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		
		SDL_TimerID sdl_timer = SDL_AddTimer(16, , void *param);
		
		window = SDL_CreateWindow(window.title, window.x, window.y, window.w, window.h, window.type);
	}
	
	~Engine()
	{
		SDL_Quit();
	}
};