#pragma once
#include <stdexcept>
#include <memory>
#include <iostream>
#include "../include/Figure.h"
#include "../include/Point.h"

template <Scalar T>
class Triangle : public Figure<T>
{
public:
    Triangle() = default;
    Triangle(const Point<T> points[3]);

    Triangle &operator=(const Triangle &other);
    Triangle &operator=(Triangle &&other) noexcept;

    bool operator==(const Figure<T> &other) const override;
    void getPointsData() const override;
    Point<T> getGeometricalCenter() const override;
    operator double() const override;
    bool isValidTriangle() const;

    template <Scalar S>
    friend std::istream &operator>>(std::istream &is, Triangle<S> &triangle);

    template <Scalar S>
    friend std::ostream &operator<<(std::ostream &os, const Triangle<S> &triangle);

    ~Triangle() noexcept = default;

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

