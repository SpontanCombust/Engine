#include <SDL2/SDL.h>

class PrimitiveRenderer
{
public:
    PrimitiveRenderer(SDL_Renderer * sdl_renderer);

    static void draw_point(int x, int y);
    static void draw_line(int x0, int y0, int x1, int y1);
    static void draw_rectangle(bool filled, int x, int y, int w, int h);

    static void naively_draw_line(int x0, int y0, int x1, int y1);

private:
    static SDL_Renderer * sdl_renderer;
};