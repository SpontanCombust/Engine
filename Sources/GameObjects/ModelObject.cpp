#include "ModelObject.hpp"

ModelObject::ModelObject() 
{
    transl_x = transl_y = 0.f;
    scale_x = scale_y = 1.f;
    rotation_deg = 0.f;
}

void ModelObject::translate( float tx, float ty ) 
{
    transl_x += tx;
    transl_y += ty;
}

void ModelObject::scale( float sx, float sy ) 
{
    scale_x += sx;
    scale_y += sy;
}

void ModelObject::rotate( float angle_deg ) 
{
    rotation_deg += angle_deg;
}

void ModelObject::scale_to_size( float size_x, float size_y ) 
{
    scale_x = size_x;
    scale_y = size_y;
}
