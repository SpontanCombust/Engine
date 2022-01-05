#pragma once

#include "ModelObject.hpp"

#include <glm/glm.hpp>

enum CollisionPolicy
{
    // do nothing about the collision
    COLLISION_POLICY_NONE        = 0,
    // if object's position can be affected by the other collider
    // if an object should be static all the time this flag shouldn't be set
    COLLISION_POLICY_AFFECTED    = 1,
    // if the object in question can affect other colliders' position
    COLLISION_POLICY_AFFECTING   = 2
};

class CollidableObject : virtual public ModelObject
{
public:
    int collision_policy; // a logic sum of CollisionPolicy flags
    glm::vec2 collider_offset;
    glm::vec2 collider_size;

    CollidableObject();

    // return true if collision happened
    virtual bool resolve_collision( CollidableObject& other_obj );
};
