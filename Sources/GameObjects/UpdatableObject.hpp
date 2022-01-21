#ifndef __UPDATABLEOBJECT_H__
#define __UPDATABLEOBJECT_H__

#include "GameObject.hpp"

#include <cstdint>

    /**
     * @brief Obiekt, który można aktualizować.
     * */
class UpdatableObject : virtual public GameObject
{
public:
/**
 * @brief Funkcja aktualizująca stan, która będzie przemianowywana 
 * 
 * @param dt Delta czasu.
 */
    virtual void update( uint32_t dt ) = 0;

    virtual ~UpdatableObject() = default;
};

#endif // __UPDATABLEOBJECT_H__