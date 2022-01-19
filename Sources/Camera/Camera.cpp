#include "Camera.hpp"

Camera::Camera() 
{
    pos = glm::vec2(0.f);
    zoom = 1.f;
}

void Camera::adjust_object_to_view( glm::vec2& transl, glm::vec2& size ) 
{
    transl  = ( transl - this->pos ) * this->zoom;
    size    = size * this->zoom;
}

void Camera::adjust_object_to_view( float& transl_x, float& transl_y, float& size_x, float& size_y ) 
{
    transl_x    = ( transl_x - this->pos.x ) * this->zoom;
    transl_y    = ( transl_y - this->pos.y ) * this->zoom;
    size_x      = size_x * this->zoom;
    size_y      = size_y * this->zoom;
}
