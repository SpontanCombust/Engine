#ifndef __MODELOBJECT_H__
#define __MODELOBJECT_H__

#include "TransformableObject.hpp"

#include <glm/glm.hpp>

// A class that stores its transformation information
class ModelObject : virtual public TransformableObject
{
public:
    glm::vec2 base_size;

    ModelObject();

    // Compute the scale to fit some arbitrary size
    virtual glm::vec2 get_target_size() const;
};

#endif // __MODELOBJECT_H__