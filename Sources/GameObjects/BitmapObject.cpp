#include "BitmapObject.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "BitmapRenderer/BitmapRenderer.hpp"

BitmapObject::BitmapObject() 
{
    tex_w = tex_h = 0;
    this->bitmap = nullptr;
    clip_rect = { 0, 0, 0, 0 };
    flip = SDL_RendererFlip::SDL_FLIP_NONE;
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

void BitmapObject::scale_to_size( float size_x, float size_y ) 
{
    scalev = { size_x / (float)tex_w, size_y / (float)tex_h };

    // preserve aspect ratio
    float scale_min = std::min( scalev.x, scalev.y );
    scalev = glm::vec2( scale_min );
}

void BitmapObject::draw() 
{
    int size_x = (int)( (float)clip_rect.w * scalev.x );
    int size_y = (int)( (float)clip_rect.h * scalev.y );
    BitmapRenderer::draw_bitmap( this->bitmap, clip_rect, (int)this->translv.x, (int)this->translv.y, size_x, size_y, this->rotation_deg, flip );
}

BitmapObject::~BitmapObject() 
{
    
}
