#ifndef __MODELOBJECT_H__
#define __MODELOBJECT_H__

#include "TransformableObject.hpp"

#include <glm/glm.hpp>

// A class that stores its transformation information
class ModelObject : virtual public TransformableObject
{
public:
    // Compute the scale to fit some arbitrary size
    virtual void set_target_size( glm::vec2 size );
    virtual glm::vec2 get_target_size() const;
};

#endif // __MODELOBJECT_H__