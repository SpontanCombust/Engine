#ifndef __TRANSFORMABLEOBJECT_H__
#define __TRANSFORMABLEOBJECT_H__

#include "GameObject.hpp"

#include <glm/glm.hpp>

    /**
     * @brief Obiekt na którym można wykonywać transformacje.
     * */
class TransformableObject : virtual public GameObject
{
public:
    glm::vec2 translation;
    glm::vec2 scale;
    float rotation_deg;

    TransformableObject();
    virtual ~TransformableObject() = default;
};

#endif // __TRANSFORMABLEOBJECT_H__