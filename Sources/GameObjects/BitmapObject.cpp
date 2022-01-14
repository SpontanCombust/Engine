#include "BitmapObject.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "Engine/Engine.hpp"

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
    float size_x, size_y;
    SDL_FRect dst_rect;

    if( adjust_to_camera )
    {
        Camera& camera = Engine::get_instance()->get_camera();

        size_x = (float)clip_rect.w * scalev.x * camera.zoom;
        size_y = (float)clip_rect.h * scalev.y * camera.zoom;

        dst_rect = {
            this->translv.x - camera.pos.x, 
            this->translv.y - camera.pos.y, 
            size_x, 
            size_y
        };
    }
    else
    {
        size_x = (float)clip_rect.w * scalev.x;
        size_y = (float)clip_rect.h * scalev.y;

        dst_rect = {
            this->translv.x, 
            this->translv.y, 
            size_x, 
            size_y
        };
    }
    
    SDL_RenderCopyExF( Engine::get_instance()->sdl_renderer, this->bitmap, &this->clip_rect, &dst_rect, this->rotation_deg, NULL, this->flip );
}

BitmapObject::~BitmapObject() 
{
    
}
