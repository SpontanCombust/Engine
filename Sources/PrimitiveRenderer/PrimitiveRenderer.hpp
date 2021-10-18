#ifndef __PRIMITIVERENDERER_H__
#define __PRIMITIVERENDERER_H__

#include "Window/Window.hpp"

#include <SDL2/SDL_render.h>

#include "../Utilities/Vector2.hpp"
#include "../Utilities/Color.hpp"

class PrimitiveRenderer
{
public:
    PrimitiveRenderer( SDL_Renderer *renderer );
    ~PrimitiveRenderer();

    void drawTriangle( Vec2i p1, Vec2i p2, Vec2i p3, Color color, bool fill = true );
    void drawRectangle( Vec2i p1, Vec2i p2, Color color, bool fill = true );
    void drawRectangle( Vec2i p, int w, int h, Color color, bool fill = true );
    void drawSquare( Vec2i p, int a, Color color, bool fill = true );
    void drawCircle( Vec2i p, int r, Color color, bool fill = true );

private:
    SDL_Renderer *sdl_renderer;
};

#endif // __PRIMITIVERENDERER_H__