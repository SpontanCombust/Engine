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

    // Scale the object based on texture size to fit the specified size
    // The scale is set so that aspect ratio of the texture is preserved 
    void scale_to_size( float size_x, float size_y ) override;

    void draw() override;
};

#endif // __BITMAPOBJECT_H__