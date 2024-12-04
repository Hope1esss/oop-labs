#pragma once
#include "Figure.h"

class Triangle : public Figure
{
public:
    Triangle() = default;
    Triangle(const Point points[3]);

    operator double() const override;
    Point geometricalCenter() const override;
    
    Triangle &operator=(const Triangle &other);
    Triangle &operator=(const Triangle &&other) noexcept;
    bool operator==(const Figure &other) const override;

    bool isValid() const;
    void printInfo() const override;

    friend std::istream &operator>>(std::istream &is, Triangle &triangle);
    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);

private:
    Point points[3];
};

class TrianglePointsCountException : public std::invalid_argument
{
public:
    TrianglePointsCountException() : std::invalid_argument("Triangle must have 3 points") {}
};

class InvalidTriangleException : public std::invalid_argument
{
public:
    InvalidTriangleException() : std::invalid_argument("Invalid triangle") {}
};