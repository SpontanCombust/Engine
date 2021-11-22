#ifndef __MODELOBJECT_H__
#define __MODELOBJECT_H__

#include "TransformableObject.hpp"

// A class that stores its transformation information
class ModelObject
{
public:
    float transl_x, transl_y;
    float scale_x, scale_y;
    float rotation_deg;

    void translate( float tx, float ty );
    void scale( float sx, float sy );
    void rotate( float angle_deg );
};

#endif // __MODELOBJECT_H__