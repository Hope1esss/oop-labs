#pragma once
#include <iostream>
class Point
{
public:
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        return os << "(" << point.x << ", " << point.y << ")";
    }

    friend std::istream &operator>>(std::istream &is, Point &point) {
        return is >> point.x >> point.y;
    }

};