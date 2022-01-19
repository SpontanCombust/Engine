#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <string>

class Animation
{
private:
    std::string name;
    SDL_Texture *used_bitmap;
    SDL_RendererFlip flip_modifier;
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
    Animation( const char *name, SDL_Texture *bitmap, SDL_RendererFlip flip_modifier, glm::ivec2 start_point, glm::ivec2 frame_size, uint32_t frame_count, uint32_t anim_duration );

    // Set the duration of a whole animation in ms
    void set_anim_duration( uint32_t anim_duration );
    SDL_Texture *get_used_bitmap() const;
    SDL_RendererFlip get_flip_modifier() const;
    const std::string& get_name() const;

    SDL_Rect get_curr_clipping_rect() const;

    /** @param num_of_iterations how many time the animation should be played; negative number for infinite times
    */
    void reset( int num_of_iterations = -1 );
    void advance( uint32_t delta_time );

    bool has_finished() const;
};

#endif // __ANIMATION_H__