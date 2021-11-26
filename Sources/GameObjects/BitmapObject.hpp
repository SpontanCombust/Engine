#ifndef __BITMAPOBJECT_H__
#define __BITMAPOBJECT_H__

#include "ModelObject.hpp"
#include "DrawableObject.hpp"

#include <SDL.h>

class BitmapObject : virtual public ModelObject, virtual public DrawableObject
{
private:
    SDL_Texture *bitmap;
    int tex_w, tex_h;

public:
    void set_bitmap( SDL_Texture *bitmap );

    void draw() override;
};

#endif // __BITMAPOBJECT_H__