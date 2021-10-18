#include "Engine/Engine.hpp"

int main()
{
	Engine *engine = Engine::get_instance();

	engine->create_window( "Test", 800, 600, WINDOWED );
	engine->start();

	return EXIT_SUCCESS;
}