#include <SDL.h>

class PrimitiveRenderer
{
public:
    PrimitiveRenderer(SDL_Renderer * sdl_renderer, int w, int h);

    static void draw_point(int x, int y);
    static void draw_line(int x0, int y0, int x1, int y1);
    static void draw_rectangle(bool filled, int x, int y, int w, int h);

    static void naively_draw_line(int x0, int y0, int x1, int y1);
    static void draw_circle(int x0, int y0, int R);

private:
    static SDL_Renderer * sdl_renderer;
    static int w;
    static int h;
};
