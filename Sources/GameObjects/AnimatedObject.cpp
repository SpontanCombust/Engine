#include "AnimatedObject.hpp"

AnimatedObject::AnimatedObject() 
{
    curr_anim = nullptr;
}

void AnimatedObject::add_animation(const Animation& anim, const char *anim_name) 
{
    Animation *already_stored = map_anim_name_to_animations[ anim_name ];
    if( !already_stored )
    {
        map_anim_name_to_animations[ anim_name ] = new Animation( anim );
    }
}

void AnimatedObject::play_animation(const char *anim_name) 
{
    Animation *anim = map_anim_name_to_animations[ anim_name ];
    if( anim )
    {
        curr_anim = anim;
        curr_anim->reset();
        bitmap = anim->get_used_bitmap();
    }
}

void AnimatedObject::update(uint32_t dt)
{
    if( curr_anim )
    {
        curr_anim->advance( dt );
        clip_rect = curr_anim->get_curr_clipping_rect();
    }
}

AnimatedObject::~AnimatedObject()
{
    for( auto it = map_anim_name_to_animations.begin(); it != map_anim_name_to_animations.end(); ++it )
    {
        delete it->second;
    }
}