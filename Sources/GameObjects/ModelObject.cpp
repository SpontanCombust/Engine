#include "ModelObject.hpp"

ModelObject::ModelObject() 
{
    base_size = {1.f, 1.f};
}

glm::vec2 ModelObject::get_target_size() const
{
    return scale * base_size;
}
