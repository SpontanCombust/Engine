#include "Engine.hpp"

Engine * Engine::engine = nullptr;

Engine::Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		LOG("Unable to initialize SDL.");
		LOG(SDL_GetError());
		exit(EXIT_FAILURE);
	}

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

	primitive_renderer = new PrimitiveRenderer(sdl_renderer);

	latency_time = 0;
	target_time = 1000 / frame_rate;

	background_color = BLACK_BACKGROUND_COLOR;

	primitive_type = NO_PRIMITIVE_TYPE;

	is_running = true;
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
		update();
		latency_time -= target_time;
	}
}

void Engine::process_events()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
						is_running = false;
					break;
				}
			break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_b:
						background_color = (background_color + 1) % BACKGROUND_COLOR_COUNT;
					break;

					case SDLK_p:
						primitive_type = (primitive_type + 1) % PRIMITIVE_TYPE_COUNT;
					break;
				}
				break;
		}
	}
}

void Engine::update()
{

}

void Engine::draw()
{
	switch (background_color)
	{
		case BLACK_BACKGROUND_COLOR:
			SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
		break;

		case RED_BACKGROUND_COLOR:
			SDL_SetRenderDrawColor(sdl_renderer, 128, 0, 0, 255);
		break;

		case GREEN_BACKGROUND_COLOR:
			SDL_SetRenderDrawColor(sdl_renderer, 0, 128, 0, 255);
		break;

		case BLUE_BACKGROUND_COLOR:
			SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 128, 255);
		break;

		case WHITE_BACKGROUND_COLOR:
			SDL_SetRenderDrawColor(sdl_renderer, 128, 128, 128, 255);
		break;
	}

	SDL_RenderClear(sdl_renderer);

switch (background_color)
		{
			case BLACK_BACKGROUND_COLOR:
				SDL_SetRenderDrawColor(sdl_renderer, 128, 128, 128, 255);
			break;

			case RED_BACKGROUND_COLOR:
				SDL_SetRenderDrawColor(sdl_renderer, 0, 128, 128, 255);
			break;

			case GREEN_BACKGROUND_COLOR:
				SDL_SetRenderDrawColor(sdl_renderer, 128, 0, 128, 255);
			break;

			case BLUE_BACKGROUND_COLOR:
				SDL_SetRenderDrawColor(sdl_renderer, 128, 128, 0, 255);
			break;

			case WHITE_BACKGROUND_COLOR:
				SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
			break;
		}

	switch (primitive_type)
	{
		case POINT_PRIMITIVE_TYPE:
			primitive_renderer->draw_point(256, 256);
		break;

		case LINE_PRIMITIVE_TYPE:
			primitive_renderer->draw_line(0, 0, 511, 511);
		break;

		case NAIVE_LINE_PRIMITIVE_TYPE:
			primitive_renderer->naively_draw_line(0, 0, 511, 511);
		break;

		case RECTANGLE_PRIMITIVE_TYPE:
			primitive_renderer->draw_rectangle(false, 0, 0, 256, 256);
		break;

		case FILLED_RECTANGLE_PRIMITIVE_TYPE:
			primitive_renderer->draw_rectangle(true, 0, 0, 256, 256);
		break;
	}

	SDL_RenderPresent(sdl_renderer);
}

Engine::~Engine()
{
	SDL_DestroyWindow(sdl_window);
	SDL_DestroyRenderer(sdl_renderer);
	delete primitive_renderer;
	
	SDL_Quit();
}