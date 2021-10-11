#ifndef __PRIMITIVERENDERER_H__
#define __PRIMITIVERENDERER_H__

#include "Color.hpp"
#include "Vector2.hpp"

#include <SDL2/SDL_render.h>

class PrimitiveRenderer
{
private:
    SDL_Renderer *m_renderer;

public:
    PrimitiveRenderer( SDL_Renderer *renderer );

    void drawTriangle( vec2i p1, vec2i p2, vec2i p3, Color color, bool fill = true );
    void drawRectangle( vec2i p1, vec2i p2, Color color, bool fill = true );
    void drawRectangle( vec2i p, int w, int h, Color color, bool fill = true );
    void drawSquare( vec2i p, int a, Color color, bool fill = true );
    void drawCircle( vec2i p, int r, Color color, bool fill = true );
};

#endif // __PRIMITIVERENDERER_H__