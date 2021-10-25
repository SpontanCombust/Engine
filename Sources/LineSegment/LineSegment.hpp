#pragma once

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
    LineSegment() = default;
    LineSegment(const Point2D & p0, const Point2D & p1);

    const Point2D & get_end_point0() const;
    const Point2D & get_end_point1() const;
    void get_end_points(Point2D & p0, Point2D & p1) const;

    void set_end_point0(const Point2D & p0);
    void set_end_point1(const Point2D & p1);
    void set_end_points(const Point2D & p0, const Point2D & p1);

    void draw(DrawAlgorithmType algorithm_type) const;

private:
    Point2D p0;
    Point2D p1;
};