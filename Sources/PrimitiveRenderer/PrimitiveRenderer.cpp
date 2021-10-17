#include "PrimitiveRenderer.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

PrimitiveRenderer::PrimitiveRenderer()
{
    
}

bool PrimitiveRenderer::has_instance = false;

PrimitiveRenderer PrimitiveRenderer::create(const Window& window)
{
    static PrimitiveRenderer primitive_renderer = PrimitiveRenderer(window);
    has_instance = true;

    return primitive_renderer;
}

PrimitiveRenderer::PrimitiveRenderer(const Window& window) 
{
    if (!has_instance)
    {
        sdl_renderer = SDL_CreateRenderer(window.sdl_window, -1, 0);
    }
}

PrimitiveRenderer::~PrimitiveRenderer()
{
    SDL_DestroyRenderer(sdl_renderer);
}

void PrimitiveRenderer::drawTriangle( Vec2i p1, Vec2i p2, Vec2i p3, Color color, bool fill ) 
{
    if( fill )
    {
        trigonRGBA( sdl_renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a );
    }
    else
    {
        filledTrigonRGBA( sdl_renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawRectangle( Vec2i p1, Vec2i p2, Color color, bool fill ) 
{
    if( fill )
    {
        rectangleRGBA( sdl_renderer, p1.x, p1.y, p2.x, p2.y, color.r, color.g, color.b, color.a );
    }
    else
    {
        boxRGBA( sdl_renderer, p1.x, p1.y, p2.x, p2.y, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawRectangle( Vec2i p, int w, int h, Color color, bool fill ) 
{
    if( fill )
    {
        rectangleRGBA( sdl_renderer, p.x, p.y, p.x + w, p.y + h, color.r, color.g, color.b, color.a );
    }
    else
    {
        boxRGBA( sdl_renderer, p.x, p.y, p.x + w, p.y + h, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawSquare( Vec2i p, int a, Color color, bool fill ) 
{
    if( fill )
    {
        rectangleRGBA( sdl_renderer, p.x, p.y, p.x + a, p.y + a, color.r, color.g, color.b, color.a );
    }
    else
    {
        boxRGBA( sdl_renderer, p.x, p.y, p.x + a, p.y + a, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawCircle(Vec2i p, int r, Color color, bool fill) 
{
    circleRGBA( sdl_renderer, p.x, p.y, r, color.r, color.g, color.b, color.a );
}
