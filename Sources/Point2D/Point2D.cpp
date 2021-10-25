#include "Point2D.hpp"

unsigned Point2D::get_x()
{
    return x;
}

unsigned Point2D::get_y()
{
    return y;
}

void Point2D::set_x(unsigned x)
{
    this->x = x;
}

void Point2D::set_y(unsigned y)
{
    this->y = y;
}

void Point2D::draw()
{
    PrimitiveRenderer::draw_point(this->x, this->y);
}