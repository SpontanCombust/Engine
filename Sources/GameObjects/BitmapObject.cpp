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

glm::vec2 BitmapObject::get_target_size() const 
{
    get_target_size( true );
}

glm::vec2 BitmapObject::get_target_size( bool keep_aspect_ratio ) const
{
    glm::vec2 target_size;

    if( keep_aspect_ratio )
    {
        target_size = ( clip_rect.w > clip_rect.h ) ? glm::vec2( base_size.x / clip_rect.w ) : glm::vec2( base_size.y / clip_rect.h );
        target_size *= glm::vec2( std::min( scale.x, scale.y ) );
    }
    else
    {
        target_size = base_size / glm::vec2( clip_rect.w, clip_rect.h );
        target_size *= scale;
    }

    return target_size;
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
