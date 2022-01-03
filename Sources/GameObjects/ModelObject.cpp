#include "ModelObject.hpp"

ModelObject::ModelObject() 
{
    translv = glm::vec2(0.f);
    scalev = glm::vec2(1.f);
    rotation_deg = 0.f;
}

void ModelObject::translate( float tx, float ty ) 
{
    translv.x += tx;
    translv.y += ty;
}

void ModelObject::scale( float sx, float sy ) 
{
    scalev.x += sx;
    scalev.y += sy;
}

void ModelObject::rotate( float angle_deg ) 
{
    rotation_deg += angle_deg;
}

void ModelObject::scale_to_size( float size_x, float size_y ) 
{
    scalev.x = size_x;
    scalev.y = size_y;
}
