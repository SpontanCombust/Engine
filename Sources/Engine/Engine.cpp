#include "Engine.hpp"
#include "GameObjects/EventListeningObject.hpp"
#include "GameObjects/UpdatableObject.hpp"
#include "GameObjects/DrawableObject.hpp"
#include "GameObjects/CollidableObject.hpp"
#include "GameObjects/AnimatedObject.hpp"
#include "BitmapRenderer/BitmapRenderer.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Engine * Engine::engine = nullptr;

Engine::Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG );
	TTF_Init();
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

	sdl_window = SDL_CreateWindow(title, x, y, w, h, window_mode);
	if (!sdl_window)
	{
		LOG("Unable to create window.");
		LOG(SDL_GetError());
		exit(EXIT_FAILURE);
	}

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
		if (!sdl_window)
	{
		LOG("Unable to create renderer.");
		LOG(SDL_GetError());
		exit(EXIT_FAILURE);
	}

	previous_time = 0;
	target_time = 1000 / frame_rate;

	is_running = true;
}

Engine::~Engine()
{
	vec_game_objects.clear();

	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);

	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

Engine * Engine::get_instance() 
{
	if(!engine)
	{
		engine = new Engine("", 0, 0, 800, 600, WindowMode::WINDOWED_MODE, 60);
	}

	return engine;
}

Engine * Engine::get_instance(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate)
{
	if (!engine)
	{
		engine = new Engine(title, x, y, w, h, window_mode, 60);
	}

	return engine;
}

void Engine::schedule()
{
	uint32_t current_time = SDL_GetTicks();
	uint32_t elapsed_time = current_time - previous_time;
	uint32_t updates_to_make = elapsed_time / target_time + 1;

	bool should_sleep = (updates_to_make == 1);

	while( updates_to_make > 0 )
	{
		remove_dead_game_objects();
		update();
		do_collisions();

		updates_to_make--;
	}

	if( should_sleep )
	{
		SDL_Delay( target_time - elapsed_time );
	}

	previous_time = current_time;
}

void Engine::process_events()
{
	SDL_Event event;
	EventListeningObject *elo;

	while (SDL_PollEvent(&event))
	{
		for( int i = 0; i < vec_game_objects.size(); i++ )
		{
			GameObject *go = vec_game_objects[i].get();
			elo = dynamic_cast<EventListeningObject *>(go);
			if( go->is_alive && elo )
			{
				elo->handle_event(event);
			}
		}

		if( event.type == SDL_QUIT )
		{
			is_running = false;
		}
	}
}

void Engine::update()
{
	UpdatableObject *updatable;

	for( int i = 0; i < vec_game_objects.size(); i++ )
	{
		GameObject *go = vec_game_objects[i].get();
		updatable = dynamic_cast<UpdatableObject *>(go);
		if( go->is_alive && updatable )
		{
			updatable->update( target_time );
		}
	}
}

void Engine::draw()
{
	SDL_RenderClear( sdl_renderer );

	DrawableObject *dob;

	for( int i = 0; i < vec_game_objects.size(); i++ )
	{
		GameObject *go = vec_game_objects[i].get();
		dob = dynamic_cast<DrawableObject *>(go);
		if( go->is_alive && dob )
		{
			dob->draw();
		}
	}

	SDL_RenderPresent(sdl_renderer);
}

void Engine::add_game_object( std::shared_ptr<GameObject> go ) 
{
	if( go )
	{
		vec_game_objects.push_back( go );
	}
}

void Engine::add_game_object( GameObject *go, bool renounce_ownership ) 
{
	if( go )
	{
		if( renounce_ownership )
		{
			vec_game_objects.push_back( std::shared_ptr<GameObject>( go ) );
		}
		else
		{
			// add a shared_ptr with an empty deletor so the object won't actually get deleted when it'll get removed
			vec_game_objects.push_back( std::shared_ptr<GameObject>( go, []( GameObject *go ){} ) );
		}
	}
}

void Engine::remove_dead_game_objects() 
{
	auto it = vec_game_objects.begin();
	while( it != vec_game_objects.end() )
	{
		if( !(*it)->is_alive )
		{
			// erase moves all subsequent elements towards the beginning of the vector 
			// and returns an iterator to the element after the erased one
			// by assigning that returned interator to `it` we iterate onto the next element
			it = vec_game_objects.erase(it);
		}
		else
		{
			// if we don't erase we simply increment the iterator
			++it;
		}
	}
}

void Engine::do_collisions() 
{
	static std::vector< CollidableObject * > vec_colliders; // gonna make this static so the memory gets allocated only once
	vec_colliders.clear();
	
	for( int i = 0; i < vec_game_objects.size(); i++ )
	{
		GameObject *go = vec_game_objects[i].get();
		CollidableObject *collidable = dynamic_cast<CollidableObject *>(go);
		if( go->is_alive && collidable )
		{
			vec_colliders.push_back( collidable );
		}
	}

	for( int i = 0; i < vec_colliders.size(); i++ )
	{
		// i+1 so an object doesn't try to resolve itself
		for( int j = i + 1; j < vec_colliders.size(); j++ )
		{
			vec_colliders[i]->resolve_collision( *vec_colliders[j] );
		}
	}
}
