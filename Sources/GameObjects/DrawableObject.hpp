#ifndef __DRAWABLEOBJECT_H__
#define __DRAWABLEOBJECT_H__

#include "GameObject.hpp"

class DrawableObject : virtual public GameObject
{
protected:
    bool adjust_to_camera;

public:
    DrawableObject();
    
    virtual void draw() = 0;
    
    virtual ~DrawableObject() = default;
};

#endif // __DRAWABLEOBJECT_H__