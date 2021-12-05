#pragma once

#include <SDL.h>

#include "Utility/Log.hpp"
#include "GameObjects/GameObject.hpp"

#include <memory>
#include <vector>

enum WindowMode
{
    WINDOWED_MODE,
    BORDERLESS_MODE = SDL_WINDOW_FULLSCREEN_DESKTOP,
    FULLSCREEN_MODE = SDL_WINDOW_FULLSCREEN
};

class Engine
{
public:
	// returns the previously created or default instance
	static Engine * get_instance();
	static Engine * get_instance(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);
	~Engine();
	bool is_running;
	void schedule();
	void process_events();
	void update();
	void draw();

	// Adds object to engine's game object pool
	// If you want the engine to let go of ther pointer, set is_alive to false in the object
	// Shares ownership over the pointer with the called
	void add_game_object( std::shared_ptr<GameObject> go );
	// Adds object to engine's game object pool
	// If you want the engine to let go of ther pointer, set is_alive to false in the object
	// Depending on renounce_ownership value, takes the ownership or only weakly references the pointer
	void add_game_object( GameObject *go, bool renounce_ownership = true );
	
public:
	SDL_Window * sdl_window;
	SDL_Renderer * sdl_renderer;


private:
	Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);
	static Engine * engine;

	uint32_t previous_time;
	uint32_t target_time;
	
	std::vector< std::shared_ptr<GameObject> > vec_game_objects;
	void remove_dead_game_objects();

	void do_collisions();
};