#include <SDL2/SDL.h>

#include "Point2D/Point2D.hpp"

class LineSegment
{
public:
    LineSegment(Point2D & p0, Point2D & p1);

    static void get_end_points(Point2D & p0, Point2D & p1);
    static void set_end_points(Point2D & p0, Point2D & p1);
    static void draw(AlgorithmType algorithm_type);

private:
    Point2D p0;
    Point2D p1;
};