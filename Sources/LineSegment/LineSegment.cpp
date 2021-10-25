#include "LineSegment.hpp"

#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

LineSegment::LineSegment(const Point2D & p0, const Point2D & p1)
{
    this->p0 = p0;
    this->p1 = p1;
}

const Point2D & LineSegment::get_end_point0() const
{
    return p0;
}

const Point2D & LineSegment::get_end_point1() const
{
    return p1;
}

void LineSegment::get_end_points(Point2D & p0, Point2D & p1) const
{
    p0 = this->p0;
    p1 = this->p1;
}

void LineSegment::set_end_point0(const Point2D & p0) 
{
    this->p0 = p0;
}

void LineSegment::set_end_point1(const Point2D & p1) 
{
    this->p1 = p1;
}

void LineSegment::set_end_points(const Point2D & p0, const Point2D & p1) 
{
    this->p0 = p0;
    this->p1 = p1;
}

void LineSegment::draw(DrawAlgorithmType algorithm_type) const
{
    if( algorithm_type == DrawAlgorithmType::NAIVE )
    {
        PrimitiveRenderer::naively_draw_line( p0.get_x(), p0.get_y(), p1.get_x(), p1.get_y() );
    }
    else
    {
        PrimitiveRenderer::draw_line( p0.get_x(), p0.get_y(), p1.get_x(), p1.get_y() );
    }
}
