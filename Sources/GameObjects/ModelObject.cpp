#include "ModelObject.hpp"

void ModelObject::set_target_size( glm::vec2 size ) 
{
    scale = size;
}

glm::vec2 ModelObject::get_target_size() const
{
    return scale;
}
