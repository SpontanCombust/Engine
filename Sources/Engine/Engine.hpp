#pragma once

#include "Utilities/Vector2.hpp"

#include <SDL2/SDL.h>

#include <string>

#include "Window/Window.hpp"

#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

class Engine
{
public:
	static Engine & create(WindowMode window_mode = WindowMode::BORDERLESS, Vec2i resolution = {1280, 720}, unsigned frame_rate = 60, bool use_mouse = true, bool use_keyboard = true, bool log_to_console = true, bool log_to_file = true, std::string log_file_name = "File.log");
	~Engine();
	bool is_running = true;
	Window window;
	PrimitiveRenderer primitive_renderer;
	void process_events();

private:
	Engine(WindowMode window_mode, Vec2i resolution, unsigned frame_rate, bool use_mouse, bool use_keyboard, bool log_to_console, bool log_to_file, std::string log_file_name);
	static bool has_instance;
	SDL_Event sdl_event;
};