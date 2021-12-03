#include "TestingGameObject.hpp"

#include "Engine/Engine.hpp"

ColorRGB enumColorToRGB( unsigned int bgc )
{
    switch (bgc)
    {
        case BLACK_BACKGROUND_COLOR:
            return { 0, 0, 0 };
        break;

        case RED_BACKGROUND_COLOR:
            return { 255, 0, 0 };
        break;

        case GREEN_BACKGROUND_COLOR:
            return { 0, 255, 0 };
        break;

        case BLUE_BACKGROUND_COLOR:
            return { 0, 0, 255 };
        break;

        case WHITE_BACKGROUND_COLOR:
            return { 255, 255, 255 };
        break;

        default:
            return { 255, 255, 255 };
    }
}

TestingGameObject::TestingGameObject() 
{
    sdl_window = Engine::get_instance()->sdl_window;
    sdl_renderer = Engine::get_instance()->sdl_renderer;

    background_color = BLACK_BACKGROUND_COLOR;
    background_color_rgb = enumColorToRGB( background_color );
	draw_color = WHITE_BACKGROUND_COLOR;
    draw_color_rgb = enumColorToRGB( draw_color );
    primitive_type = NO_PRIMITIVE_TYPE;

    int w, h;
    SDL_GetWindowSize( sdl_window, &w, &h );
    canvas = SDL_CreateTexture( sdl_renderer, SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_TARGET, w, h );
	is_brush_held = false;
}

TestingGameObject::~TestingGameObject() 
{
    SDL_DestroyTexture( canvas );
}

void TestingGameObject::draw() 
{
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
			PrimitiveRenderer::draw_point(256, 256);
		break;

		case LINE_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_line(0, 0, 511, 511);
		break;

		case RECTANGLE_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_rectangle(false, 0, 0, 256, 256);
		break;

		case FILLED_RECTANGLE_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_rectangle(true, 0, 0, 256, 256);
		break;

		case NAIVE_LINE_PRIMITIVE_TYPE:
			PrimitiveRenderer::naively_draw_line(0, 0, 511, 511);
		break;

		case CIRCLE_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_circle(256, 256, 64);
		break;

		case ELLIPSE_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_ellipse(256, 256, 64, 32);
		break;

		case MULTILINE_OPEN_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_multiline_open( multiline_example_points, DrawAlgorithmType::SDL );
		break;

		case MULTILINE_CLOSED_PRIMITIVE_TYPE:
			PrimitiveRenderer::draw_multiline_closed( multiline_example_points, DrawAlgorithmType::SDL );
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
}

void TestingGameObject::handle_event(const SDL_Event& e) 
{
    switch( e.type )
    {
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
                case SDLK_b:
                    background_color = (background_color + 1) % BACKGROUND_COLOR_COUNT;
                    background_color_rgb = enumColorToRGB( background_color ); 
                break;

                case SDLK_f:
                    draw_color = (draw_color + 1) % BACKGROUND_COLOR_COUNT;
                    draw_color_rgb = enumColorToRGB( draw_color );
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
            if( e.button.button == SDL_BUTTON_LEFT )
            {
                is_brush_held = true;
                brush_x = e.button.x;
                brush_y = e.button.y;
            }
            else if( e.button.button == SDL_BUTTON_RIGHT )
            {
                SDL_SetRenderTarget( sdl_renderer, canvas );
                SDL_SetRenderDrawColor( sdl_renderer, background_color_rgb.r, background_color_rgb.g, background_color_rgb.b, 255 );
                PrimitiveRenderer::flood_fill(e.button.x, e.button.y, background_color_rgb, draw_color_rgb ); 
                SDL_SetRenderTarget( sdl_renderer, NULL );
            }
        break;

        case SDL_MOUSEBUTTONUP:
            if( e.button.button == SDL_BUTTON_LEFT )
            {
                is_brush_held = false;
            }
        break;

        case SDL_MOUSEMOTION:
            brush_x = e.motion.x;
            brush_y = e.motion.y;
        break;
    }
}
