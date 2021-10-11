#include "PrimitiveRenderer.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

PrimitiveRenderer::PrimitiveRenderer( SDL_Renderer *renderer ) 
{
    m_renderer = renderer;
}

void PrimitiveRenderer::drawTriangle( vec2i p1, vec2i p2, vec2i p3, Color color, bool fill ) 
{
    if( fill )
    {
        trigonRGBA( m_renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a );
    }
    else
    {
        filledTrigonRGBA( m_renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawRectangle( vec2i p1, vec2i p2, Color color, bool fill ) 
{
    if( fill )
    {
        rectangleRGBA( m_renderer, p1.x, p1.y, p2.x, p2.y, color.r, color.g, color.b, color.a );
    }
    else
    {
        boxRGBA( m_renderer, p1.x, p1.y, p2.x, p2.y, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawRectangle( vec2i p, int w, int h, Color color, bool fill ) 
{
    if( fill )
    {
        rectangleRGBA( m_renderer, p.x, p.y, p.x + w, p.y + h, color.r, color.g, color.b, color.a );
    }
    else
    {
        boxRGBA( m_renderer, p.x, p.y, p.x + w, p.y + h, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawSquare( vec2i p, int a, Color color, bool fill ) 
{
    if( fill )
    {
        rectangleRGBA( m_renderer, p.x, p.y, p.x + a, p.y + a, color.r, color.g, color.b, color.a );
    }
    else
    {
        boxRGBA( m_renderer, p.x, p.y, p.x + a, p.y + a, color.r, color.g, color.b, color.a );
    }
}

void PrimitiveRenderer::drawCircle(vec2i p, int r, Color color, bool fill) 
{
    circleRGBA( m_renderer, p.x, p.y, r, color.r, color.g, color.b, color.a );
}
