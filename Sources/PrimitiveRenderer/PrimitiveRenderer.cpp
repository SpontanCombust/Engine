#include "PrimitiveRenderer.hpp"

#include <cmath>

SDL_Renderer * PrimitiveRenderer::sdl_renderer = nullptr;
int PrimitiveRenderer::w = 0;
int PrimitiveRenderer::h = 0;

PrimitiveRenderer::PrimitiveRenderer(SDL_Renderer * sdl_renderer, int w, int h)
{
    this->sdl_renderer = sdl_renderer;
    this->w = w;
    this->h = h;
}

void PrimitiveRenderer::draw_point(int x, int y)
{
    SDL_RenderDrawPoint(sdl_renderer, x, y);
    SDL_RenderPresent(sdl_renderer);
}

void PrimitiveRenderer::draw_line(int x0, int y0, int x1, int y1)
{
    SDL_RenderDrawLine(sdl_renderer, x0, y0, x1, y1);
}

void PrimitiveRenderer::draw_rectangle(bool filled, int x, int y, int w, int h)
{
    SDL_Rect sdl_rectangle = {x, y, w, h};

    if (!filled)
    {
        SDL_RenderDrawRect(sdl_renderer, &sdl_rectangle);   
    }

    else
    {
        SDL_RenderFillRect(sdl_renderer, &sdl_rectangle);
    }
}
//FIXME fails to draw in all possible scenarios
void PrimitiveRenderer::naively_draw_line(int x0, int y0, int x1, int y1)
{
    float m = (float)(y1 - y0) / (float)(x1 - x0);

    if (fabs(m) <= 1)
    {
        float yi = (float)y0;

        for (unsigned xi = x0; xi < (unsigned)x1; ++xi)
        {
            draw_point((unsigned)xi, (unsigned)((float)yi + 0.5f));
            yi += m;
        }
    }

    else
    {
        m = (float)(x1 - x0) / (float)(y1 - y0);
        float xi = (float)x0;

        for (unsigned yi = y0; yi < (unsigned)y1; ++yi)
        {
            draw_point(xi + 0.5f, yi);
            xi += m;
        }
    }
}

void PrimitiveRenderer::draw_circle(int x0, int y0, int R)
{
    float step = 1.0f / R;

    for (float a = 0.0f; a < M_PI / 4.0f; a += step)
    {
        float x = x0 + R * cosf(a) + 0.5f;
        float y = y0 + R * sinf(a) + 0.5f;
        PrimitiveRenderer::draw_point((unsigned)x, (unsigned)y);
        PrimitiveRenderer::draw_point((unsigned)x, (unsigned)512 - y);
        PrimitiveRenderer::draw_point((unsigned)w - x, (unsigned)y);
        PrimitiveRenderer::draw_point((unsigned)w - x, (unsigned)h - y);
        PrimitiveRenderer::draw_point((unsigned)y, (unsigned)x);
        PrimitiveRenderer::draw_point((unsigned)y, (unsigned)w - x);
        PrimitiveRenderer::draw_point((unsigned)h - y, (unsigned)x);
        PrimitiveRenderer::draw_point((unsigned)h - y, (unsigned)w - x);
    }
}

void PrimitiveRenderer::draw_ellipse(int x0, int y0, int Rx, int Ry)
{
    float step = 1.0f / Rx;

    for (float a = 0.0f; a < M_PI * 2; a += step)
    {
        float x = x0 + Rx * cosf(a);
        float y = y0 + Ry * sinf(a);
        PrimitiveRenderer::draw_point(x, y);
    }
}

void PrimitiveRenderer::draw_multiline_open(const std::vector<Point2D>& points, DrawAlgorithmType algorithm_type) 
{
    if(points.size() > 1)
    {
        // create a drawing function pointer
        // this way we check for drawing type only once instead of every time we draw each line
        void (*line_drawing_func)(int,int,int,int);
        if(algorithm_type == DrawAlgorithmType::NAIVE)
        {
            line_drawing_func = naively_draw_line;
        }
        else
        {
            line_drawing_func = draw_line;
        }

        for (size_t i = 0; i < points.size() - 1; i++)
        {
            line_drawing_func( points[i].get_x(), points[i].get_y(), points[i+1].get_x(), points[i+1].get_y() );
        }
    }
}

void PrimitiveRenderer::draw_multiline_closed(const std::vector<Point2D>& points, DrawAlgorithmType algorithm_type) 
{
    if(points.size() > 1)
    {
        // create a drawing function pointer
        // this way we check for drawing type only once instead of every time we draw each line
        void (*line_drawing_func)(int,int,int,int);
        if(algorithm_type == DrawAlgorithmType::NAIVE)
        {
            line_drawing_func = naively_draw_line;
        }
        else
        {
            line_drawing_func = draw_line;
        }

        for (size_t i = 0; i < points.size() - 1; i++)
        {
            line_drawing_func( points[i].get_x(), points[i].get_y(), points[i+1].get_x(), points[i+1].get_y() );
        }

        // draw a line going from the first to last point, successfully closing the shape
        line_drawing_func( points[0].get_x(), points[0].get_y(), points[points.size() - 1].get_x(), points[points.size() - 1].get_y() );
    }
}

void PrimitiveRenderer::flood_fill(int x, int y, uint32_t fill_color, uint32_t boundary_color)
{
    std::stack<Point2D> stack;
    stack.push(Point2D(x, y));
    while (!stack.empty())
    {
        Point2D point2D = stack.top();
        stack.pop();
        if (point2D.get_x() >= 512)
        {
            continue;
        }
        if (point2D.get_y() >= 512)
        {
            continue;
        }
        SDL_Rect  sdl_rect = { point2D.get_x(), point2D.get_y(), 1, 1 };
        uint32_t pixel;
        SDL_RenderReadPixels(PrimitiveRenderer::sdl_renderer, &sdl_rect, SDL_PIXELFORMAT_RGBA8888, &pixel, 4);
        if (pixel == fill_color)
        {
            continue;
        }

        else if (pixel != boundary_color)
        {
            continue;
        }

        else
        {
            SDL_SetRenderDrawColor(PrimitiveRenderer::sdl_renderer, fill_color >> 24 & 0xFF, fill_color >> 16 & 0xFF, fill_color >> 8 & 0xFF, fill_color & 0xFF);
            draw_point(point2D.get_x(), point2D.get_y());
        }

        stack.push(Point2D(point2D.get_x(), point2D.get_y() + 1));
        stack.push(Point2D(point2D.get_x(), point2D.get_y() - 1));
        stack.push(Point2D(point2D.get_x() - 1, point2D.get_y()));
        stack.push(Point2D(point2D.get_x() + 1, point2D.get_y()));
    }
}