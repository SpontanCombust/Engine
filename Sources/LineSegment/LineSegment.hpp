#include <SDL.h>

#include "Point2D/Point2D.hpp"

enum class DrawAlgorithmType
{
    NAIVE,
    SDL
};

class LineSegment
{
public:
    LineSegment(Point2D & p0, Point2D & p1);

    void get_end_points(Point2D & p0, Point2D & p1);
    void set_end_points(Point2D & p0, Point2D & p1);
    void draw(DrawAlgorithmType algorithm_type);

private:
    Point2D p0;
    Point2D p1;
};