#include "PrimitiveRenderer.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>


PrimitiveRenderer::PrimitiveRenderer( SDL_Renderer *renderer ) 
{
    sdl_renderer = renderer;
}

PrimitiveRenderer::~PrimitiveRenderer() 
{

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
