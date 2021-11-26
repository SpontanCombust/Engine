#ifndef __UPDATABLEOBJECT_H__
#define __UPDATABLEOBJECT_H__

#include "GameObject.hpp"

#include <cstdint>

class UpdatableObject : virtual public GameObject
{
public:
    virtual void update( uint32_t dt ) = 0;

    virtual ~UpdatableObject() = default;
};

#endif // __UPDATABLEOBJECT_H__