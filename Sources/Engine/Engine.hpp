#pragma once

#include <SDL.h>

#include "Utility/Log.hpp"
#include "PrimitiveRenderer/PrimitiveRenderer.hpp"
#include "Utility/Color.hpp"
#include "GameObjects/GameObject.hpp"

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

	// Takes ownership over the pointer and adds it to engine's game object pool
	void add_game_object( GameObject *go );
	
public:
	SDL_Window * sdl_window;
	SDL_Renderer * sdl_renderer;


private:
	Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);
	static Engine * engine;

	PrimitiveRenderer * primitive_renderer;

	uint32_t previous_time;
	uint32_t latency_time;
	uint32_t target_time;
	
	std::vector< GameObject * > vec_game_objects;
	void remove_dead_game_objects();
};