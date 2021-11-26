#define ENGINE_TEST

#include <cstdlib>

#include "Engine/Engine.hpp"
#include "Testing/TestingGameObject.hpp"

#include "GameObjects/AnimatedObject.hpp"

#include <SDL_image.h>

#undef main

int main()
{

	IMG_Init(IMG_INIT_PNG);
	Engine * engine = Engine::get_instance("Tech Demo", 64, 64, 512, 512, WINDOWED_MODE, 60);
	
#ifdef CHECK_SINGLETON
	engine = Engine::get_instance("Tech Demo", 64, 64, 512, 512, WINDOWED_MODE, 60);
#endif

#ifdef ENGINE_TEST
	engine->add_game_object( new TestingGameObject() );
#endif 

	AnimatedObject vulture(4, 0, 4);
	const char paths[4][128] = { "1.png", "2.png", "3.png", "4.png" };
	for (unsigned index = 0; index < 4; ++index)
	{
		SDL_Texture *texture = NULL;
    	SDL_Surface *surface = IMG_Load(paths[index]);
		if (surface) {
			texture = SDL_CreateTextureFromSurface(engine->sdl_renderer, surface);
			SDL_FreeSurface(surface);
		}
		vulture.bitmaps[index] = texture;
	}
	engine->add_game_object(&vulture);

	while (engine->is_running)
	{
		engine->process_events();
		engine->schedule();
		engine->draw();
	}

	delete engine;

	return EXIT_SUCCESS;
}