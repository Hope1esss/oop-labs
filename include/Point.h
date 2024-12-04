#pragma once
#include <iostream>

class Point
{
public:
    double x, y;

    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    friend std::istream &operator>>(std::istream &is, Point &point)
    {
        is >> point.x >> point.y;
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << "("  << point.x << ", " << point.y << ")";
        return os;
    }
};
