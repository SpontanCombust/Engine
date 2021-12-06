#include "Point2D.hpp"

#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

#include <cmath>


Point2D::Point2D() 
{
    this->x = 0;
    this->y = 0;
}

Point2D::Point2D( int x, int y ) 
{
    this->x = x;
    this->y = y;
}

int Point2D::get_x() const
{
    return x;
}

int Point2D::get_y() const
{
    return y;
}

void Point2D::set_x(int x)
{
    this->x = x;
}

void Point2D::set_y(int y)
{
    this->y = y;
}

void Point2D::draw()
{
    PrimitiveRenderer::draw_point(this->x, this->y);
}

void Point2D::translate( float transl_x, float transl_y ) 
{
    x += (int)transl_x;
    y += (int)transl_y;
}

void Point2D::scale( float scale_x, float scale_y ) 
{
    x *= (int)scale_x;
    y *= (int)scale_y;
}

void Point2D::rotate( float angle_deg ) 
{
    int x1 = x;

    x = x1 * std::cos( angle_deg ) - y * std::sin( angle_deg );
    y = x1 * std::sin( angle_deg ) + y * std::cos( angle_deg );
}
