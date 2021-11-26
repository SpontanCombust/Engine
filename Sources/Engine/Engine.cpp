#include "Engine.hpp"
#include "GameObjects/EventListeningObject.hpp"
#include "GameObjects/UpdatableObject.hpp"
#include "GameObjects/DrawableObject.hpp"
#include "BitmapRenderer/BitmapRenderer.hpp"

#include <SDL_ttf.h>
#include "GameObjects/AnimatedObject.hpp"

Engine * Engine::engine = nullptr;

Engine::Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

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

	primitive_renderer = new PrimitiveRenderer(sdl_renderer, w, h);
	BitmapRenderer::setup( sdl_renderer );

	latency_time = 0;
	target_time = 1000 / frame_rate;

	is_running = true;
}

Engine::~Engine()
{
	for( GameObject *go : vec_game_objects )
	{
		delete go;
	}
	vec_game_objects.clear();

	delete primitive_renderer;
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);

	
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
	latency_time += SDL_GetTicks() - previous_time;

	while (latency_time >= target_time)
	{
		remove_dead_game_objects();
		update();
		latency_time -= target_time;
	}
}

void Engine::process_events()
{
	SDL_Event event;
	EventListeningObject *elo;

	while (SDL_PollEvent(&event))
	{
		for( int i = 0; i < vec_game_objects.size(); i++ )
		{
			GameObject *go = vec_game_objects[i];

			if( elo = dynamic_cast<EventListeningObject *>(go) )
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
		GameObject *go = vec_game_objects[i];

		if( updatable = dynamic_cast<UpdatableObject *>(go) )
		{
			updatable->update( target_time );
		}
		if( updatable = dynamic_cast<AnimatedObject *>(go) )
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
		GameObject *go = vec_game_objects[i];

		if( dob = dynamic_cast<DrawableObject *>(go) )
		{
			dob->draw();
		}
	}

	SDL_RenderPresent(sdl_renderer);
}

void Engine::add_game_object( GameObject *go ) 
{
	if( go )
	{
		vec_game_objects.push_back( go );
	}
}

void Engine::remove_game_object( GameObject *go ) 
{
    if( go )
    {
        for( auto it = vec_game_objects.begin(); it != vec_game_objects.end(); )
        {
            if( *it == go )
            {
                it = vec_game_objects.erase( it );
            }
            else
            {
                ++it;
            }
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
			delete *it;
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
