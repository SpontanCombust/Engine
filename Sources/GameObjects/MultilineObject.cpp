#include "MultilineObject.hpp"

#include "PrimitiveRenderer/PrimitiveRenderer.hpp"

MultilineObject::MultilineObject(std::vector<Point2D> points) 
{
    this->points = points;
}

void MultilineObject::draw() 
{
    PrimitiveRenderer::draw_multiline_closed( points, DrawAlgorithmType::SDL );
}

void MultilineObject::translate(float tx, float ty) 
{
    for( Point2D& p : points )
    {
        p.translate(tx, ty);
    }
}

void MultilineObject::scale(float sx, float sy) 
{
    for( Point2D& p : points )
    {
        p.scale(sx, sy);
    }
}

void MultilineObject::rotate(float angle_deg) 
{
    for( Point2D& p : points )
    {
        p.rotate(angle_deg);
    }
}
