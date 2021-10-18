#pragma once

#include "Utilities/Vector2.hpp"

#include <SDL2/SDL.h>

#include <string>

#include "Window/Window.hpp"

#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

class Engine
{
public:
	static Engine *get_instance();
	~Engine();

	void start();
	void stop();

	Window& create_window( const char *title, int w, int h, WindowMode window_mode );
	Window& get_window();

private:
	Engine();
	static Engine *instance;

	Window window;
	bool is_running;
	void process_events();
};