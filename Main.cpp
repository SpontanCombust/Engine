#include <cstdlib>

#include "Window.hpp"
#include "Engine.hpp"

int main()
{
	SDL_DisplayMode sdl_display_mode;
	
	if (SDL_GetDesktopDisplayMode(0, &sdl_display_mode))
	{
		exit(EXIT_FAILURE);
	}
	
	Window window("Engine", 0, 0, sdl_display_mode.w, sdl_display_mode.h, FULLSCREEN);
	
	Engine engine(window);
	
	
	
	return EXIT_SUCCESS;
}