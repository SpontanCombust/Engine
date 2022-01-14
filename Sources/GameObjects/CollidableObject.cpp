#include "CollidableObject.hpp"

#include <cmath>

CollidableObject::CollidableObject() 
{
    collision_policy = COLLISION_POLICY_NONE;
    collider_offset = glm::vec2(0.f);
    collider_size = glm::vec2(0.f);
}


inline bool can_affect( int policyFlags )
{
    return ( policyFlags & COLLISION_POLICY_AFFECTING ) > 0;
}

inline bool can_be_affected( int policyFlags )
{
    return ( policyFlags & COLLISION_POLICY_AFFECTED ) > 0;
}

inline bool can_affect_or_be_affected( int policyFlags )
{
    return ( policyFlags & ( COLLISION_POLICY_AFFECTING | COLLISION_POLICY_AFFECTED ) ) > 0;
}

inline bool can_affect_and_be_affected( int policyFlags )
{
    return ( policyFlags & ( COLLISION_POLICY_AFFECTING | COLLISION_POLICY_AFFECTED ) ) == ( COLLISION_POLICY_AFFECTING | COLLISION_POLICY_AFFECTED );
}

bool CollidableObject::resolve_collision( CollidableObject& other_obj ) 
{
    glm::vec2 this_half_extents = collider_size * scale / 2.f;
    glm::vec2 other_half_extents = other_obj.collider_size * other_obj.scale / 2.f;

    // vector coming from the center of other AABB to this AABB 
    glm::vec2 this_center_to_other_center = ( other_obj.translation + other_obj.collider_offset * other_obj.scale + other_half_extents ) - ( translation + collider_offset * scale + this_half_extents );

    if( std::abs( this_center_to_other_center.x ) <= ( this_half_extents.x + other_half_extents.x ) && std::abs( this_center_to_other_center.y ) <= ( this_half_extents.y + other_half_extents.y ) )
    {
        if( can_affect_or_be_affected( collision_policy ) || can_affect_or_be_affected( other_obj.collision_policy ) )
        {
            glm::vec2 displacement;

            if( this_center_to_other_center.x >= 0.f )
            {
                displacement.x = this_center_to_other_center.x - this_half_extents.x - other_half_extents.x;
            }
            else
            {
                displacement.x = this_center_to_other_center.x + this_half_extents.x + other_half_extents.x;
            }

            if( this_center_to_other_center.y >= 0.f )
            {
                displacement.y = this_center_to_other_center.y - this_half_extents.y - other_half_extents.y;
            }
            else
            {
                displacement.y = this_center_to_other_center.y + this_half_extents.y + other_half_extents.y;
            }


            if( std::abs( displacement.x ) < std::abs( displacement.y ) )
            {
                displacement.y = 0.f;
            }
            else
            {
                displacement.x = 0.f;
            }
            

            if( can_affect_and_be_affected( collision_policy ) && can_affect_and_be_affected( other_obj.collision_policy ) )
            {
                translation += displacement / 2.f;
                other_obj.translation -= displacement / 2.f;
            }
            // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
            else if( can_be_affected( collision_policy ) && can_affect( other_obj.collision_policy ) )
            {
                translation += displacement;
            }
            // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
            else if( can_affect( collision_policy ) && can_be_affected( other_obj.collision_policy ) )
            {
                other_obj.translation -= displacement;
            }
        }

        return true;
    }

    return false;
}
