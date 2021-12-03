#include "Animation.hpp"

Animation::Animation( SDL_Texture *bitmap, Point2D start_point, Size2D frame_size, uint32_t frame_count, uint32_t anim_duration ) 
{
    this->used_bitmap = bitmap;
    this->frame_start_rect = { start_point.get_x(), start_point.get_y(), frame_size.get_x(), frame_size.get_y() };
    this->frame_count = frame_count;
    this->anim_duration = anim_duration;

    this->anim_timer = 0; 
    curr_clipping_rect = frame_start_rect;
}

void Animation::set_anim_duration( uint32_t anianim_durationm_time ) 
{
    this->anim_duration = anim_duration;
}

SDL_Texture* Animation::get_used_bitmap() const
{
    return used_bitmap;
}

SDL_Rect Animation::get_curr_clipping_rect() const
{
    return curr_clipping_rect;
}

void Animation::reset() 
{
    this->anim_timer = 0; 
    curr_clipping_rect = frame_start_rect;
}

void Animation::advance( uint32_t delta_time ) 
{
    anim_timer += delta_time;
    anim_timer = anim_timer % anim_duration;
    int frame_index = anim_timer / (anim_duration / frame_count);

    curr_clipping_rect = {
        frame_start_rect.x + frame_index * frame_start_rect.w,
        frame_start_rect.y,
        frame_start_rect.w,
        frame_start_rect.h
    };
}
