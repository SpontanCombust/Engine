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

void BitmapObject::draw() 
{
    glm::vec2 target_scale = glm::vec2( std::min( this->scale.x, this->scale.y ) ); // to keep aspect ratio

    SDL_FRect dst_rect = {
        this->translation.x, 
        this->translation.y,
        this->clip_rect.w * target_scale.x,
        this->clip_rect.h * target_scale.y
    };

    if( adjust_to_camera )
    {
        Camera& camera = Engine::get_instance()->get_camera();

        dst_rect.x -= camera.pos.x;
        dst_rect.y -= camera.pos.y;
        dst_rect.w *= camera.zoom;
        dst_rect.h *= camera.zoom;
    }
    
    SDL_RenderCopyExF( Engine::get_instance()->sdl_renderer, this->bitmap, &this->clip_rect, &dst_rect, this->rotation_deg, NULL, this->flip );
}

BitmapObject::~BitmapObject() 
{
    
}
