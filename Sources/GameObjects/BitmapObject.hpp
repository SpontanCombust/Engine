#ifndef __BITMAPOBJECT_H__
#define __BITMAPOBJECT_H__

#include "ModelObject.hpp"
#include "DrawableObject.hpp"

#include <SDL.h>

class BitmapObject : virtual public ModelObject, virtual public DrawableObject
{
public:
    glm::ivec2 tex_size;
    SDL_Texture *bitmap;
    SDL_Rect clip_rect;
    SDL_RendererFlip flip;
    
    BitmapObject();
    BitmapObject( SDL_Texture *bitmap );
    BitmapObject( const char *bitmap_file_path );

    ~BitmapObject();

    void set_bitmap( SDL_Texture *bitmap );

    glm::vec2 get_target_size() const override;
    virtual glm::vec2 get_target_size( bool keep_aspect_ratio ) const;

    void draw() override;
};

#endif // __BITMAPOBJECT_H__