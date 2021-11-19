#include "PrimitiveRenderer.hpp"

#include <cmath>
#include <cstring>

SDL_Renderer * PrimitiveRenderer::sdl_renderer = nullptr;
int PrimitiveRenderer::window_w = 0;
int PrimitiveRenderer::window_h = 0;

PrimitiveRenderer::PrimitiveRenderer(SDL_Renderer * sdl_renderer, int w, int h)
{
    this->sdl_renderer = sdl_renderer;
    this->window_w = w;
    this->window_h = h;
}

void PrimitiveRenderer::draw_point(int x, int y)
{
    SDL_RenderDrawPoint(sdl_renderer, x, y);
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
        PrimitiveRenderer::draw_point((unsigned)window_w - x, (unsigned)y);
        PrimitiveRenderer::draw_point((unsigned)window_w - x, (unsigned)window_h - y);
        PrimitiveRenderer::draw_point((unsigned)y, (unsigned)x);
        PrimitiveRenderer::draw_point((unsigned)y, (unsigned)window_w - x);
        PrimitiveRenderer::draw_point((unsigned)window_h - y, (unsigned)x);
        PrimitiveRenderer::draw_point((unsigned)window_h - y, (unsigned)window_w - x);
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

void PrimitiveRenderer::flood_fill(int x, int y, ColorRGB fill_color, ColorRGB boundary_color)
{
    SDL_PixelFormat *pixel_format = SDL_AllocFormat( SDL_PIXELFORMAT_RGBA32 );
    uint32_t mapped_fill_color = SDL_MapRGB( pixel_format, fill_color.r, fill_color.g, fill_color.b );
    uint32_t mapped_boundary_color = SDL_MapRGB( pixel_format, boundary_color.r, boundary_color.g, boundary_color.b );
    SDL_FreeFormat( pixel_format );

    std::stack<Point2D> stack;
    stack.push(Point2D(x, y));

    uint32_t *window_pixels;
    window_pixels = new uint32_t[ window_w * window_h ];
    SDL_Rect rect { 0, 0, window_w, window_h };
    SDL_RenderReadPixels(sdl_renderer, &rect, SDL_PIXELFORMAT_RGBA32, window_pixels, window_w * sizeof(uint32_t) );

    while (!stack.empty())
    {
        Point2D point2D = stack.top();
        stack.pop();

        if (point2D.get_x() < 0 || point2D.get_x() >= window_w)
        {
            continue;
        }
        if (point2D.get_y() < 0 || point2D.get_y() >= window_h)
        {
            continue;
        }

        uint32_t *pixel = &window_pixels[ point2D.get_y() * window_w + point2D.get_x() ];
        if (*pixel == mapped_fill_color)
        {
            continue;
        }
        else if (*pixel != mapped_boundary_color)
        {
            *pixel = mapped_fill_color;

            stack.push(Point2D(point2D.get_x(), point2D.get_y() + 1));
            stack.push(Point2D(point2D.get_x(), point2D.get_y() - 1));
            stack.push(Point2D(point2D.get_x() - 1, point2D.get_y()));
            stack.push(Point2D(point2D.get_x() + 1, point2D.get_y()));
        }       
    }

    SDL_Texture *color_buffer = SDL_CreateTexture( sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, window_w, window_h );
    uint32_t *color_buffer_pixels;
    int pitch;
    SDL_LockTexture( color_buffer, NULL, (void **)&color_buffer_pixels, &pitch );
    memcpy( color_buffer_pixels, window_pixels, window_w * window_h * sizeof(uint32_t) );
    SDL_UnlockTexture( color_buffer );

    SDL_RenderCopy( sdl_renderer, color_buffer, NULL, NULL );

    delete window_pixels;
    SDL_DestroyTexture( color_buffer );
}