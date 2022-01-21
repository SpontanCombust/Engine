#ifndef __MODELOBJECT_H__
#define __MODELOBJECT_H__

#include "TransformableObject.hpp"

#include <glm/glm.hpp>

// A class that stores its transformation information
/**
 * @brief Klasa obiektów przechowujących informację o transformacji.
 * 
 */
class ModelObject : virtual public TransformableObject
{
public:
    // Compute the scale to fit some arbitrary size
    /**
     * @brief Ustawia rozmiar obiektu
     * 
     * @param size Rozmiar.
     */
    virtual void set_target_size( glm::vec2 size );

    /**
     * @brief Uzyskaj rozmiar docelowego obiektu.
     * 
     * @return glm::vec2 
     */
    virtual glm::vec2 get_target_size() const;
};

#endif // __MODELOBJECT_H__