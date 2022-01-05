#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec2 pos;
    float zoom;

    Camera();
};