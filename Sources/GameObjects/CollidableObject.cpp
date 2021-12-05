#include "CollidableObject.hpp"

#include "../Utility/Vector2.hpp"

#include <cmath>

CollidableObject::CollidableObject() 
{
    collision_policy = COLLISION_POLICY_NONE;
    collider_width = collider_height = 0.f;
}


inline bool can_affect( CollisionPolicy policyFlags )
{
    return ( policyFlags & COLLISION_POLICY_AFFECTING ) > 0;
}

inline bool can_be_affected( CollisionPolicy policyFlags )
{
    return ( policyFlags & COLLISION_POLICY_AFFECTED ) > 0;
}

inline bool can_affect_or_be_affected( CollisionPolicy policyFlags )
{
    return ( policyFlags & ( COLLISION_POLICY_AFFECTING | COLLISION_POLICY_AFFECTED ) ) > 0;
}

inline bool can_affect_and_be_affected( CollisionPolicy policyFlags )
{
    return ( policyFlags & ( COLLISION_POLICY_AFFECTING | COLLISION_POLICY_AFFECTED ) ) == ( COLLISION_POLICY_AFFECTING | COLLISION_POLICY_AFFECTED );
}

bool CollidableObject::resolve_collision( CollidableObject& other_obj ) 
{
    vec2f this_half_extents { 
        collider_width * scale_x / 2.f, 
        collider_height * scale_y / 2.f 
    };
    vec2f other_half_extents { 
        other_obj.collider_width * other_obj.scale_x / 2.f, 
        other_obj.collider_height * other_obj.scale_y / 2.f 
    };

    // vector coming from the center of other AABB to this AABB 
    vec2f this_center_to_other_center { 
        other_obj.transl_x + other_half_extents.x - (transl_x + this_half_extents.x),
        other_obj.transl_y + other_half_extents.y - (transl_y + this_half_extents.y)
    };

    if( std::abs( this_center_to_other_center.x ) <= ( this_half_extents.x + other_half_extents.x ) && std::abs( this_center_to_other_center.y ) <= ( this_half_extents.y + other_half_extents.y ) )
    {
        if( can_affect_or_be_affected( collision_policy ) || can_affect_or_be_affected( other_obj.collision_policy ) )
        {
            vec2f displacement;

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
            

            if( can_affect_and_be_affected( collision_policy ) && can_affect_and_be_affected( collision_policy ) )
            {
                transl_x += displacement.x / 2.f;
                transl_y += displacement.y / 2.f;
                other_obj.transl_x -= displacement.x / 2.f;
                other_obj.transl_y -= displacement.y / 2.f;
            }
            // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
            else if( can_be_affected( collision_policy ) && can_affect( other_obj.collision_policy ) )
            {
                transl_x += displacement.x;
                transl_y += displacement.y;
            }
            // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
            else if( can_affect( collision_policy ) && can_be_affected( other_obj.collision_policy ) )
            {
                other_obj.transl_x -= displacement.x;
                other_obj.transl_y -= displacement.y;
            }
        }

        return true;
    }

    return false;
}
