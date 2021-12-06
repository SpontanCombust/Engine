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
    x = (int)( (float)x + transl_x );
    y = (int)( (float)y + transl_y );
}

void Point2D::scale( float scale_x, float scale_y ) 
{
    x = (int)( (float)x * scale_x );
    y = (int)( (float)y * scale_y );
}

inline float deg_to_rand( float angle_deg )
{
    return angle_deg * M_PI / 180.f;
}

void Point2D::rotate( float angle_deg ) 
{
    float x1 = (float)x;

    float _cos = std::cos( deg_to_rand( angle_deg ) );
    float _sin = std::sin( deg_to_rand( angle_deg ) );

    x = (int)( x1 * _cos - (float)y * _sin );
    y = (int)( x1 * _sin + (float)y * _cos );
}
