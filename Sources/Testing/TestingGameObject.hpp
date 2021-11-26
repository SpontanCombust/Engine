#pragma once

#include "GameObjects/EventListeningObject.hpp"
#include "GameObjects/DrawableObject.hpp"
#include "Utility/Color.hpp"

#include <SDL.h>

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
	CANVAS_PRIMITIVE_TYPE,
	PRIMITIVE_TYPE_COUNT
};

class TestingGameObject : virtual public DrawableObject, virtual public EventListeningObject
{
private:
    unsigned background_color;
	ColorRGB background_color_rgb;
	unsigned int draw_color;
	ColorRGB draw_color_rgb;
	unsigned primitive_type;

	SDL_Texture *canvas;
	bool is_brush_held;
	int brush_x, brush_y;

    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

public:
    TestingGameObject();
    ~TestingGameObject();

    void draw() override;

    void handle_event( const SDL_Event& e ) override;
};