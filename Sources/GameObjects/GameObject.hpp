#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class GameObject
{
public:
    bool is_alive;

    GameObject();
    virtual ~GameObject() = default; // interface needs at least virtual destructor
};

#endif // __GAMEOBJECT_H__