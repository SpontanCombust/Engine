#ifndef __TRANSFORMABLEOBJECT_H__
#define __TRANSFORMABLEOBJECT_H__

#include "GameObject.hpp"

class TransformableObject : virtual public GameObject
{
public:
    virtual void translate( float tx, float ty ) = 0;
    virtual void scale( float sx, float sy ) = 0;
    virtual void rotate( float angle_deg ) = 0;

    virtual ~TransformableObject() = default;
};

#endif // __TRANSFORMABLEOBJECT_H__