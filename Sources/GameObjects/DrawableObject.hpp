#ifndef __DRAWABLEOBJECT_H__
#define __DRAWABLEOBJECT_H__

#include "GameObject.hpp"

/**
 * @brief Interfejs do rysowania obiektów na ekran.
 * 
 */
class DrawableObject : virtual public GameObject
{
protected:
/**
 * @brief Czy obiekt ma być dopasowany do kamery?
 * 
 */
    bool adjust_to_camera;

public:
    DrawableObject();
    
    /**
     * @brief Narysuj obiekt na ekranie.
     * 
     */
    virtual void draw() = 0;
    
    virtual ~DrawableObject() = default;
};

#endif // __DRAWABLEOBJECT_H__