#include "LineSegment.hpp"

LineSegment::LineSegment(Point2D & p0, Point2D & p1)
{
    this->p0 = p0;
    this->p1 = p1;
}

void get_end_points(Point2D & p0, Point2D & p1)
{
    p0 = this->p0;
    p1 = this->p1;
}