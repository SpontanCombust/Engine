#include "AnimatedObject.hpp"

AnimatedObject::AnimatedObject( SDL_Texture *bitmap, Size2D frame_size, uint32_t frame_count, uint32_t frame_length) 
: BitmapObject( bitmap ) 
{
    this->frame_size = frame_size;
    this->frame_count = frame_count;
    this->frame_length = frame_length;
    this->frame_index = 0;
    this->anim_timer = 0;
}

AnimatedObject::AnimatedObject( const char *bitmap_file_path, Size2D frame_size, uint32_t frame_count, uint32_t frame_length) 
: BitmapObject( bitmap_file_path ) 
{
    this->frame_size = frame_size;
    this->frame_count = frame_count;
    this->frame_length = frame_length;
    this->frame_index = 0;
    this->anim_timer = 0;
}

void AnimatedObject::update(uint32_t dt)
{
    anim_timer += dt;
    anim_timer = anim_timer % (frame_count * frame_length);
    frame_index = anim_timer / frame_length;

    //FIXME for now this is just one animation for the whole object
    clip_rect = { 
        (int)frame_index * frame_size.get_x(),
        0,
        frame_size.get_x(),
        frame_size.get_y()
    };
}

AnimatedObject::~AnimatedObject()
{
    
}