#ifndef __ANIMATEDOBJECT_H__
#define __ANIMATEDOBJECT_H__

#include "BitmapObject.hpp"
#include "UpdatableObject.hpp"

class AnimatedObject : virtual public BitmapObject, virtual public UpdatableObject
{
public:
    void update(uint32_t dt) override;
    uint32_t frame_count = 1;
    uint32_t frame_index = 0;
    uint32_t frame_length = 1;
    SDL_Texture **bitmaps;
    AnimatedObject(uint32_t frame_count, uint32_t frame_index, uint32_t frame_length);
    ~AnimatedObject();
};

#endif // __ANIMATEDOBJECT_H__