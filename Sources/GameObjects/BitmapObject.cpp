#include "BitmapObject.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "Engine/Engine.hpp"

BitmapObject::BitmapObject() 
{
    tex_size = { 0, 0 };
    this->bitmap = nullptr;
    clip_rect = { 0, 0, 0, 0 };
    flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

BitmapObject::BitmapObject(SDL_Texture *bitmap) 
{
    set_bitmap( bitmap );
    flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

BitmapObject::BitmapObject( const char *bitmap_file_path ) 
{
    set_bitmap( ResourceManager::load_bitmap( bitmap_file_path ) );
    flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

void BitmapObject::set_bitmap( SDL_Texture *bitmap ) 
{
    this->bitmap = bitmap;
    SDL_QueryTexture( bitmap, NULL, NULL, &this->tex_size.x, &this->tex_size.y );
    clip_rect = { 0, 0, tex_size.x, tex_size.y };
}

void BitmapObject::set_target_size( glm::vec2 size ) 
{
    set_target_size( size, true );
}

void BitmapObject::set_target_size( glm::vec2 size, bool keep_aspect_ratio ) 
{
    if( keep_aspect_ratio )
    {
        this->scale = ( clip_rect.w < clip_rect.h ) ? glm::vec2( size.x / clip_rect.w ) : glm::vec2( size.y / clip_rect.h );
    }
    else
    {
        this->scale = size / glm::vec2( clip_rect.w, clip_rect.h );
    }
}

glm::vec2 BitmapObject::get_target_size() const 
{
    return scale * glm::vec2( clip_rect.w, clip_rect.h );
}

void BitmapObject::draw() 
{
    glm::vec2 target_size = get_target_size();

    SDL_FRect dst_rect = {
        this->translation.x, 
        this->translation.y,
        target_size.x,
        target_size.y
    };

    if( adjust_to_camera )
    {
        Camera& camera = Engine::get_instance()->get_camera();
        camera.adjust_object_to_view( dst_rect.x, dst_rect.y, dst_rect.w, dst_rect.h );
    }
    
    SDL_RenderCopyExF( Engine::get_instance()->sdl_renderer, this->bitmap, &this->clip_rect, &dst_rect, this->rotation_deg, NULL, this->flip );
}

BitmapObject::~BitmapObject() 
{
    
}
