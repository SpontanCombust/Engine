#ifndef __ANIMATEDOBJECT_H__
#define __ANIMATEDOBJECT_H__

#include "BitmapObject.hpp"
#include "UpdatableObject.hpp"
#include "Point2D/Point2D.hpp"

class AnimatedObject : virtual public BitmapObject, virtual public UpdatableObject
{
private:
    uint32_t frame_count;
    uint32_t frame_length;
    Size2D frame_size;

    uint32_t anim_timer;
    uint32_t frame_index;

public:
    AnimatedObject( SDL_Texture *bitmap, Size2D frame_size, uint32_t frame_count, uint32_t frame_length);
    AnimatedObject( const char *bitmap_file_path, Size2D frame_size, uint32_t frame_count, uint32_t frame_length);
    ~AnimatedObject();

    void update(uint32_t dt) override;
};

#endif // __ANIMATEDOBJECT_H__