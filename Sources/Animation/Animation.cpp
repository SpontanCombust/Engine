#include "Animation.hpp"

Animation::Animation( const char *name, SDL_Texture *bitmap, SDL_RendererFlip flip_modifier, Point2D start_point, Size2D frame_size, uint32_t frame_count, uint32_t anim_duration ) 
{
    this->name = name;
    this->used_bitmap = bitmap;
    this->flip_modifier = flip_modifier;
    this->frame_start_rect = { start_point.get_x(), start_point.get_y(), frame_size.get_x(), frame_size.get_y() };
    this->frame_count = frame_count;
    this->anim_duration = anim_duration;

    this->anim_timer = 0; 
    this->iterations_left = 0;
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

SDL_RendererFlip Animation::get_flip_modifier() const
{
    return flip_modifier;
}

const std::string& Animation::get_name() const
{
    return name;
}

SDL_Rect Animation::get_curr_clipping_rect() const
{
    return curr_clipping_rect;
}

void Animation::reset( int num_of_iterations ) 
{
    this->anim_timer = 0;
    this->iterations_left = num_of_iterations;
    curr_clipping_rect = frame_start_rect;
}

void Animation::advance( uint32_t delta_time ) 
{
    if( iterations_left != 0 )
    {
        anim_timer += delta_time;
        int iteration_done = anim_timer / anim_duration;

        anim_timer = anim_timer % anim_duration;

        const uint32_t frame_duration = anim_duration / frame_count;
        int frame_index = anim_timer / frame_duration;

        curr_clipping_rect = {
            frame_start_rect.x + frame_index * frame_start_rect.w,
            frame_start_rect.y,
            frame_start_rect.w,
            frame_start_rect.h
        };

        if( iterations_left > 0)
        {
            iterations_left -= iteration_done;
        }
    }
}

bool Animation::has_finished() const
{
    return iterations_left == 0;
}
