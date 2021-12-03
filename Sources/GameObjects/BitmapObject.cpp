#include "BitmapObject.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "BitmapRenderer/BitmapRenderer.hpp"

BitmapObject::BitmapObject() 
{
    this->bitmap = nullptr;
    clip_rect = { 0, 0, 0, 0 };
}

BitmapObject::BitmapObject(SDL_Texture *bitmap) 
{
    set_bitmap( bitmap );
}

BitmapObject::BitmapObject( const char *bitmap_file_path ) 
{
    set_bitmap( ResourceManager::load_bitmap( bitmap_file_path ) );
}

void BitmapObject::set_bitmap( SDL_Texture *bitmap ) 
{
    this->bitmap = bitmap;
    SDL_QueryTexture( bitmap, NULL, NULL, &this->tex_w, &this->tex_h );
    clip_rect = { 0, 0, tex_w, tex_h };
}

void BitmapObject::draw() 
{
    int size_x = (int)( (float)clip_rect.w * scale_x );
    int size_y = (int)( (float)clip_rect.h * scale_y );
    BitmapRenderer::draw_bitmap( this->bitmap, clip_rect, (int)this->transl_x, (int)this->transl_y, size_x, size_y, this->rotation_deg );
}

BitmapObject::~BitmapObject() 
{
    
}
