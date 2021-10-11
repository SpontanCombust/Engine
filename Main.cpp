#include <cstdlib>

#include "Log.hpp"
#include "Window.hpp"
#include "Engine.hpp"

int main()
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		LOG("Unable to initialize SDL: " << SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_DisplayMode sdl_display_mode;
	
	if( SDL_GetDesktopDisplayMode(0, &sdl_display_mode) < 0 )
	{
		exit(EXIT_FAILURE);
	}
	
	Window window("Engine", 0, 0, sdl_display_mode.w, sdl_display_mode.h, FULLSCREEN);
	
	Engine engine(window);

	SDL_Delay(2000);
	
	
	
	return EXIT_SUCCESS;
}