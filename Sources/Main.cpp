#define ENGINE_TEST

#include "Engine/Engine.hpp"
#include "Testing/TestingGameObject.hpp"

#include "GameObjects/AnimatedObject.hpp"

#include <SDL_image.h>

int main()
{
	Engine * engine = Engine::get_instance("Tech Demo", 64, 64, 512, 512, WINDOWED_MODE, 60);
	
#ifdef CHECK_SINGLETON
	engine = Engine::get_instance("Tech Demo", 64, 64, 512, 512, WINDOWED_MODE, 60);
#endif

#ifdef ENGINE_TEST
	engine->add_game_object( new TestingGameObject() );
	
	auto obj = new AnimatedObject( "../test_assets/Vulture_walk.png", Size2D( 48, 48 ), 4, 500 );
	obj->scale_x = obj->scale_y = 2.f;
	obj->transl_x = obj->transl_y = 300.f;
	engine->add_game_object( obj );
#endif 

	while (engine->is_running)
	{
		engine->process_events();
		engine->schedule();
		engine->draw();
	}

	delete engine;

	return EXIT_SUCCESS;
}