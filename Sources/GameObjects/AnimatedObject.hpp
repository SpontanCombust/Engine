#ifndef __ANIMATEDOBJECT_H__
#define __ANIMATEDOBJECT_H__

#include "BitmapObject.hpp"
#include "UpdatableObject.hpp"
#include "Animation/Animation.hpp"

#include <unordered_map>

class AnimatedObject : virtual public BitmapObject, virtual public UpdatableObject
{
private:
    std::unordered_map<std::string, Animation *> map_anim_name_to_animations;
    Animation *curr_anim;

public:
    AnimatedObject();
    ~AnimatedObject() override;

    void add_animation( const Animation& anim, const char *anim_name );
    void play_animation( const char *anim_name );

    void update(uint32_t dt) override;
};

#endif // __ANIMATEDOBJECT_H__