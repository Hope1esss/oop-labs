#pragma once
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point{
    T x, y;
    Point(): x(0), y(0) {}
    Point(T x, T y): x(x), y(y) {}

    friend std::istream &operator>>(std::istream &is, Point &point)
    {
        return is >> point.x >> point.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        return os << "(" <<point.x << ", " << point.y << ")";
    }
};