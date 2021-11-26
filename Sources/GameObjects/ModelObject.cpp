#include "ModelObject.hpp"

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
