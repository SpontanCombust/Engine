#include "AnimatedObject.hpp"

AnimatedObject::AnimatedObject() 
{
    curr_anim = nullptr;
}

AnimatedObject::~AnimatedObject()
{
    for( auto it = map_anim_name_to_animations.begin(); it != map_anim_name_to_animations.end(); ++it )
    {
        delete it->second;
    }
}

void AnimatedObject::add_animation( const Animation& anim ) 
{
    Animation *already_stored = map_anim_name_to_animations[ anim.get_name() ];
    if( !already_stored )
    {
        map_anim_name_to_animations[ anim.get_name() ] = new Animation( anim );
    }
}

void AnimatedObject::play_animation(const char *anim_name, int iterations) 
{
    Animation *anim = map_anim_name_to_animations[ anim_name ];
    if( anim )
    {
        curr_anim = anim;
        curr_anim->reset( iterations );
        bitmap = anim->get_used_bitmap();
        flip = anim->get_flip_modifier();
    }
}

bool AnimatedObject::has_animation_finished() const
{
    if( curr_anim )
    {
        return curr_anim->has_finished();
    }

    return false;
}

std::string AnimatedObject::get_animation_name() const
{
    if( !curr_anim )
    {
        return "";
    }
    
    return curr_anim->get_name();
}

void AnimatedObject::update(uint32_t dt)
{
    if( curr_anim )
    {
        curr_anim->advance( dt );
        clip_rect = curr_anim->get_curr_clipping_rect();
    }
}
