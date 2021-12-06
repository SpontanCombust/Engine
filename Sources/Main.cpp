#define ENGINE_TEST

#include "Engine/Engine.hpp"
#include "Testing/TestingGameObject.hpp"

#include "GameObjects/AnimatedObject.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include <SDL_image.h>

int main()
{
	Engine * engine = Engine::get_instance("Tech Demo", 64, 64, 512, 512, WINDOWED_MODE, 60);
	
#ifdef CHECK_SINGLETON
	engine = Engine::get_instance("Tech Demo", 64, 64, 512, 512, WINDOWED_MODE, 60);
#endif

#ifdef ENGINE_TEST
	engine->add_game_object( new TestingGameObject() );
	
	auto obj = new AnimatedObject();
	obj->scale_x = obj->scale_y = 2.f;
	obj->transl_x = obj->transl_y = 300.f;
	obj->add_animation( Animation( "walk", ResourceManager::load_bitmap("../test_assets/Vulture_walk.png"), SDL_FLIP_HORIZONTAL, Point2D(0,0), Size2D(48,48), 4, 1500 ) );
	obj->play_animation( "walk", 5 );
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