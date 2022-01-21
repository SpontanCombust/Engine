#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
/**
 * @brief Pozycja kamery.
 * 
 */
    glm::vec2 pos;

/**
 * @brief Przybliżenie kamery.
 * 
 */
    float zoom;

    Camera();

/**
 * @brief Transformuje podane własności obiektu do obecnych ustawień kamery.
 * @param transl przesunięcie
 * @param size rozmiar
 */
    void adjust_object_to_view( glm::vec2& transl, glm::vec2& size );

/**
 * @brief Transformuje podane własności obiektu do obecnych ustawień kamery.
 * @param transl_x przesunięcie, współrzędna x
 * @param transl_y przesunięcie, współrzędna y
 * @param size_x skala, współrzędna x
 * @param size_y skala, współrzędna y
 */
    void adjust_object_to_view( float& transl_x, float& transl_y, float& size_x, float& size_y );
};