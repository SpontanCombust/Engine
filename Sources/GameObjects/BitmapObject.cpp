#include "BitmapObject.hpp"

#include "BitmapRenderer/BitmapRenderer.hpp"

void BitmapObject::set_bitmap(SDL_Texture *bitmap) 
{
    this->bitmap = bitmap;
    SDL_QueryTexture( bitmap, NULL, NULL, &this->tex_w, &this->tex_h );
}

void BitmapObject::draw() 
{
    int size_x = (int)( (float)tex_w * scale_x );
    int size_y = (int)( (float)tex_h * scale_y );
    BitmapRenderer::draw_bitmap( this->bitmap, (int)this->transl_x, (int)this->transl_y, size_x, size_y, this->rotation_deg );
}
