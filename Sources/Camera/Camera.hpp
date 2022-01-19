#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec2 pos;
    float zoom;

    Camera();

    void adjust_object_to_view( glm::vec2& transl, glm::vec2& size );
    void adjust_object_to_view( float& transl_x, float& transl_y, float& size_x, float& size_y );
};