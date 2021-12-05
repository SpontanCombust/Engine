#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Point2D/Point2D.hpp"

#include <SDL.h>

#include <cstdint>

class Animation
{
private:
    SDL_Texture *used_bitmap;
    SDL_Rect frame_start_rect;
    uint32_t frame_count;
    uint32_t anim_duration;

    uint32_t anim_timer;
    int iterations_left;
    SDL_Rect curr_clipping_rect;


public:
    /**
     * @brief Constructor
     * 
     * @param bitmap bitmap to be used for animation; it's not actually actively used by the class, only stored 
     * @param start_point point in pixels in the bitmap to start the animation from
     * @param frame_size size in pixels of every frame in the animation
     * @param frame_count how many individual frames there are in the animation
     * @param anim_duration how long the animation should last in milliseconds
     */
    Animation( SDL_Texture *bitmap, Point2D start_point, Size2D frame_size, uint32_t frame_count, uint32_t anim_duration );

    // Set the duration of a whole animation in ms
    void set_anim_duration( uint32_t anim_duration );

    SDL_Texture *get_used_bitmap() const;

    SDL_Rect get_curr_clipping_rect() const;

    /** @param num_of_iterations how many time the animation should be played; negative number for infinite times
    */
    void reset( int num_of_iterations = -1 );
    void advance( uint32_t delta_time );

    bool has_finished() const;
};

#endif // __ANIMATION_H__