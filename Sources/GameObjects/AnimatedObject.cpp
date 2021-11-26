#include "AnimatedObject.hpp"

AnimatedObject::AnimatedObject(uint32_t frame_count, uint32_t frame_index, uint32_t frame_length)
{
    this->frame_count = frame_count;
    this->frame_index = frame_index;
    this->frame_length = frame_length;
    bitmaps = new SDL_Texture*[frame_count];
}

void AnimatedObject::update(uint32_t dt)
{
    frame_index = dt < 1000 / 60 / frame_count;
    bitmap = bitmaps[frame_index];
    draw();
}

AnimatedObject::~AnimatedObject()
{
    delete[] bitmaps;
}