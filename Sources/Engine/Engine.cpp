#include "Engine.hpp"
#include "GameObjects/EventListeningObject.hpp"
#include "GameObjects/UpdatableObject.hpp"
#include "GameObjects/DrawableObject.hpp"

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

	primitive_renderer = new PrimitiveRenderer(sdl_renderer, w, h);

	latency_time = 0;
	target_time = 1000 / frame_rate;

	background_color = BLACK_BACKGROUND_COLOR;
	draw_color = WHITE_BACKGROUND_COLOR;

	primitive_type = NO_PRIMITIVE_TYPE;

	is_running = true;

	canvas = SDL_CreateTexture( sdl_renderer, SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_TARGET, w, h );
	is_brush_held = false;
}

Engine::~Engine()
{
	remove_dead_game_objects();

	SDL_DestroyTexture( canvas );

	SDL_DestroyWindow(sdl_window);
	SDL_DestroyRenderer(sdl_renderer);
	delete primitive_renderer;

	
	SDL_Quit();
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
		for( GameObject *go : vec_game_objects )
		{
			if( elo = dynamic_cast<EventListeningObject *>(go) )
			{
				elo->handle_event(event);
			}
		}

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

						switch (background_color)
						{
							case BLACK_BACKGROUND_COLOR:
								background_color_rgb = { 0, 0, 0 };
							break;

							case RED_BACKGROUND_COLOR:
								background_color_rgb = { 255, 0, 0 };
							break;

							case GREEN_BACKGROUND_COLOR:
								background_color_rgb = { 0, 255, 0 };
							break;

							case BLUE_BACKGROUND_COLOR:
								background_color_rgb = { 0, 0, 255 };
							break;

							case WHITE_BACKGROUND_COLOR:
								background_color_rgb = { 255, 255, 255 };
							break;
						}
					break;

					case SDLK_f:
						draw_color = (draw_color + 1) % BACKGROUND_COLOR_COUNT;

						switch (draw_color)
						{
							case BLACK_BACKGROUND_COLOR:
								draw_color_rgb = { 0, 0, 0 };
							break;

							case RED_BACKGROUND_COLOR:
								draw_color_rgb = { 255, 0, 0 };
							break;

							case GREEN_BACKGROUND_COLOR:
								draw_color_rgb = { 0, 255, 0 };
							break;

							case BLUE_BACKGROUND_COLOR:
								draw_color_rgb = { 0, 0, 255 };
							break;

							case WHITE_BACKGROUND_COLOR:
								draw_color_rgb = { 255, 255, 255 };
							break;
						}
					break;

					case SDLK_p:
						primitive_type = (primitive_type + 1) % PRIMITIVE_TYPE_COUNT;
					break;
				}
				{
					std::string title = "Draw[F]: " + draw_color_rgb.to_string() + "\t" + "Background/Fill[B]: " + background_color_rgb.to_string();
					SDL_SetWindowTitle( sdl_window, title.c_str() );
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				if( event.button.button == SDL_BUTTON_LEFT )
				{
					is_brush_held = true;
					brush_x = event.button.x;
					brush_y = event.button.y;
				}
				else if( event.button.button == SDL_BUTTON_RIGHT )
				{
					SDL_SetRenderTarget( sdl_renderer, canvas );
					SDL_SetRenderDrawColor( sdl_renderer, background_color_rgb.r, background_color_rgb.g, background_color_rgb.b, 255 );
					PrimitiveRenderer::flood_fill(event.button.x, event.button.y, background_color_rgb, draw_color_rgb ); 
					SDL_SetRenderTarget( sdl_renderer, NULL );
				}
			break;

			case SDL_MOUSEBUTTONUP:
				if( event.button.button == SDL_BUTTON_LEFT )
				{
					is_brush_held = false;
				}
			break;

			case SDL_MOUSEMOTION:
				brush_x = event.motion.x;
				brush_y = event.motion.y;
			break;
		}
	}
}

void Engine::update()
{
	UpdatableObject *updatable;

	for( GameObject *go : vec_game_objects )
	{
		if( updatable = dynamic_cast<UpdatableObject *>(go) )
		{
			updatable->update( target_time );
		}
	}
}

void Engine::draw()
{
	DrawableObject *dob;
	for( GameObject *go : vec_game_objects )
	{
		if( dob = dynamic_cast<DrawableObject *>(go) )
		{
			dob->draw();
		}
	}

	SDL_SetRenderDrawColor( sdl_renderer, background_color_rgb.r, background_color_rgb.g, background_color_rgb.b, 255 );
	SDL_RenderClear(sdl_renderer);
	SDL_SetRenderDrawColor( sdl_renderer, draw_color_rgb.r, draw_color_rgb.g, draw_color_rgb.b, 255 );

	std::vector<Point2D> multiline_example_points;
	multiline_example_points.push_back( Point2D{ 150, 400 } );
	multiline_example_points.push_back( Point2D{ 150, 200 } );
	multiline_example_points.push_back( Point2D{ 200, 300 } );
	multiline_example_points.push_back( Point2D{ 250, 200 } );
	multiline_example_points.push_back( Point2D{ 300, 300 } );
	multiline_example_points.push_back( Point2D{ 350, 200 } );
	multiline_example_points.push_back( Point2D{ 350, 400 } );

	switch (primitive_type)
	{
		case POINT_PRIMITIVE_TYPE:
			primitive_renderer->draw_point(256, 256);
		break;

		case LINE_PRIMITIVE_TYPE:
			primitive_renderer->draw_line(0, 0, 511, 511);
		break;

		case RECTANGLE_PRIMITIVE_TYPE:
			primitive_renderer->draw_rectangle(false, 0, 0, 256, 256);
		break;

		case FILLED_RECTANGLE_PRIMITIVE_TYPE:
			primitive_renderer->draw_rectangle(true, 0, 0, 256, 256);
		break;

		case NAIVE_LINE_PRIMITIVE_TYPE:
			primitive_renderer->naively_draw_line(0, 0, 511, 511);
		break;

		case CIRCLE_PRIMITIVE_TYPE:
			primitive_renderer->draw_circle(256, 256, 64);
		break;

		case ELLIPSE_PRIMITIVE_TYPE:
			primitive_renderer->draw_ellipse(256, 256, 64, 32);
		break;

		case MULTILINE_OPEN_PRIMITIVE_TYPE:
			primitive_renderer->draw_multiline_open( multiline_example_points, DrawAlgorithmType::SDL );
		break;

		case MULTILINE_CLOSED_PRIMITIVE_TYPE:
			primitive_renderer->draw_multiline_closed( multiline_example_points, DrawAlgorithmType::SDL );
		break;

		case CANVAS_PRIMITIVE_TYPE:
			if( is_brush_held )
			{
				SDL_SetRenderTarget( sdl_renderer, canvas );
				PrimitiveRenderer::draw_rectangle( true, brush_x, brush_y, 5, 5 );
				SDL_SetRenderTarget( sdl_renderer, NULL );
			}

			SDL_RenderCopy( sdl_renderer, canvas, NULL, NULL );
		break;
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
