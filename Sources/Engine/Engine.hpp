#pragma once

#include <SDL.h>

#include "Utility/Log.hpp"
#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

enum WindowMode
{
    WINDOWED_MODE,
    BORDERLESS_MODE = SDL_WINDOW_FULLSCREEN_DESKTOP,
    FULLSCREEN_MODE = SDL_WINDOW_FULLSCREEN
};

enum BackgroundColor
{
	BLACK_BACKGROUND_COLOR,
	RED_BACKGROUND_COLOR,
	GREEN_BACKGROUND_COLOR,
	BLUE_BACKGROUND_COLOR,
	WHITE_BACKGROUND_COLOR,
	BACKGROUND_COLOR_COUNT
};

enum PrimitiveType
{
	NO_PRIMITIVE_TYPE,
	POINT_PRIMITIVE_TYPE,
	LINE_PRIMITIVE_TYPE,
	RECTANGLE_PRIMITIVE_TYPE,
	FILLED_RECTANGLE_PRIMITIVE_TYPE,
	NAIVE_LINE_PRIMITIVE_TYPE,
	CIRCLE_PRIMITIVE_TYPE,
	ELLIPSE_PRIMITIVE_TYPE,
	MULTILINE_OPEN_PRIMITIVE_TYPE,
	MULTILINE_CLOSED_PRIMITIVE_TYPE,
	PRIMITIVE_TYPE_COUNT
};

class Engine
{
public:
	static Engine * get_instance(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);
	~Engine();
	bool is_running;
	void schedule();
	void process_events();
	void update();
	void draw();
	
private:
	Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);
	static Engine * engine;

	SDL_Window * sdl_window;
	SDL_Renderer * sdl_renderer;
	PrimitiveRenderer * primitive_renderer;

	uint32_t previous_time;
	uint32_t latency_time;
	uint32_t target_time;

	SDL_Event event;

	unsigned background_color;
	unsigned primitive_type;
};