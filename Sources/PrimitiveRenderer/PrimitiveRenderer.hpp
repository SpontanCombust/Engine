#pragma once

#include "Point2D/Point2D.hpp"
#include "LineSegment/LineSegment.hpp"
#include "Utility/Color.hpp"

#include <SDL.h>

#include <vector>
#include <stack>

class PrimitiveRenderer
{
public:
    PrimitiveRenderer(SDL_Renderer * sdl_renderer, int w, int h);

    static void draw_point(int x, int y);
    static void draw_line(int x0, int y0, int x1, int y1);
    static void draw_rectangle(bool filled, int x, int y, int w, int h);

    static void naively_draw_line(int x0, int y0, int x1, int y1);
    static void draw_circle(int x0, int y0, int R);
    static void draw_ellipse(int x0, int y0, int Rx, int Ry);

    static void draw_multiline_open( const std::vector<Point2D>& points, DrawAlgorithmType algorithm_type );
    static void draw_multiline_closed( const std::vector<Point2D>& points, DrawAlgorithmType algorithm_type );

    static void flood_fill(int x, int y, ColorRGB fill_color, ColorRGB boundary_color);

public:
    static SDL_Renderer * sdl_renderer;
private:
    static int window_w;
    static int window_h;
};
