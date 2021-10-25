#include "Point2D.hpp"

#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

Point2D::Point2D() 
{
    this->x = 0;
    this->y = 0;
}

Point2D::Point2D( unsigned int x, unsigned int y ) 
{
    this->x = x;
    this->y = y;
}

unsigned Point2D::get_x() const
{
    return x;
}

unsigned Point2D::get_y() const
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

void Point2D::draw() const
{
    PrimitiveRenderer::draw_point(this->x, this->y);
}