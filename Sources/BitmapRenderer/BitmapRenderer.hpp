#ifndef __BITMAPRENDERER_H__
#define __BITMAPRENDERER_H__

#include <SDL.h>

class BitmapRenderer
{
public:
    static void setup( SDL_Renderer *renderer );

    //FIXME might need to be moved elsewhere
    static SDL_Texture *load_bitmap_from_file( const char *file_path );

    static void draw_bitmap( SDL_Texture *bitmap, int pos_x, int pos_y, int size_x, int size_y, float rot );
    static void draw_bitmap( SDL_Texture *bitmap, SDL_Rect clipRect, int pos_x, int pos_y, int size_x, int size_y, float rot );

private:
    static SDL_Renderer *sdl_renderer;
};

#endif // __BITMAPRENDERER_H__