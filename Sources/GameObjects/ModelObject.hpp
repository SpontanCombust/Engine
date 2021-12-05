#ifndef __MODELOBJECT_H__
#define __MODELOBJECT_H__

#include "TransformableObject.hpp"

// A class that stores its transformation information
class ModelObject : virtual public TransformableObject
{
public:
    float transl_x, transl_y;
    float scale_x, scale_y;
    float rotation_deg;

    ModelObject();

    void translate( float tx, float ty ) override;
    void scale( float sx, float sy ) override;
    void rotate( float angle_deg ) override;

    // Compute the scale to fit some arbitrary size
    virtual void scale_to_size( float size_x, float size_y );
};

#endif // __MODELOBJECT_H__