#include "PrimitiveRenderer.hpp"

SDL_Renderer * PrimitiveRenderer::sdl_renderer = nullptr;

PrimitiveRenderer::PrimitiveRenderer(SDL_Renderer * sdl_renderer)
{
    this->sdl_renderer = sdl_renderer;
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

void PrimitiveRenderer::naively_draw_line(int x0, int y0, int x1, int y1)
{
    float m = (float)(y1 - y0) / (float)(x1 - x0);

    if (fabs(m) <= 1)
    {
        float yi = y0;

        for (unsigned xi = x0; xi < x1; ++xi)
        {
            draw_point(xi, yi + 0.5);
            yi += m;
        }
    }

    else
    {
        m = (float)(x1 - x0) / (float)(y1 - y0);
        float xi = x0;

        for (unsigned yi = y0; yi < y1; ++yi)
        {
            draw_point(xi + 0.5, yi);
            xi += m;
        }
    }
}

void PrimitiveRenderer::draw_circle(int x0, int y0, int R)
{
    float step = 1.0f / R;

    for (float a = 0.0f; a < 2.0f * M_PI; a += step)
    {
        float x = x0 + R * cos(a) + 0.5f;
        float y = y0 + R * sin(a) + 0.5f;
        PrimitiveRenderer::draw_point(x, y);
    }
}
