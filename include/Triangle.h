#pragma once
#include "../include/Figure.h"

template <Scalar T>
class Triangle : public Figure<T>
{
public:
    Triangle() = default;
    Triangle(const Point<T> points[3]);

    Triangle &operator=(const Triangle &other);
    Triangle &operator=(Triangle &&other) noexcept;

    bool operator==(const Figure &other) const override;
    operator double() const override;
    Point<T> getGeometricalCenter() const override;
    void getPointsData() const override;
    bool isValidTriangle() const;

    friend std::istream &operator>>(std::istream &is, Triangle<T> &triangle);
    friend std::ostream &operator<<(std::ostream &os, const Triangle<T> &triangle);

private:
    std::unique_ptr<Point<T>> points[3];
};

class TrianglePointsException : public std::invalid_argument
{
public:
    TrianglePointsException() : std::invalid_argument("Invalid numbers of points for triangle. It should be 3 points") {}
};

class TriangleValidationException : public std::invalid_argument
{
public:
    TriangleValidationException() : std::invalid_argument("Points can't form valid triangle") {}
};