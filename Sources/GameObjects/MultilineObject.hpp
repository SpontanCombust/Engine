#pragma once

#include "DrawableObject.hpp"
#include "TransformableObject.hpp"
#include "Point2D/Point2D.hpp"

#include <vector>

class MultilineObject : virtual public DrawableObject, virtual public TransformableObject
{
private:
    std::vector<Point2D> points;
    
public:
    MultilineObject( std::vector<Point2D> points );

    void draw() override;

    void translate( float tx, float ty ) override;
    void scale( float sx, float sy ) override;
    void rotate( float angle_deg ) override;
};