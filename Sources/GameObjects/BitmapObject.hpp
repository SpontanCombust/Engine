#ifndef __BITMAPOBJECT_H__
#define __BITMAPOBJECT_H__

#include "ModelObject.hpp"
#include "DrawableObject.hpp"

#include <SDL.h>

class BitmapObject : virtual public ModelObject, virtual public DrawableObject
{
public:
    int tex_w, tex_h;
    SDL_Texture *bitmap;
    SDL_Rect clip_rect;
    SDL_RendererFlip flip;
    
    BitmapObject();
    BitmapObject( SDL_Texture *bitmap );
    BitmapObject( const char *bitmap_file_path );

    ~BitmapObject();

    void set_bitmap( SDL_Texture *bitmap );

    void draw() override;
};

#endif // __BITMAPOBJECT_H__