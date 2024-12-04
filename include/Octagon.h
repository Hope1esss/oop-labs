#pragma once
#include "Figure.h"

class Octagon : public Figure
{
public:
    Octagon() = default;
    Octagon(const Point points[3]);

    operator double() const override;
    Point geometricalCenter() const override;
    
    Octagon &operator=(const Octagon &other);
    Octagon &operator=(const Octagon &&other) noexcept;
    bool operator==(const Figure &other) const override;

    bool isValid() const;
    void printInfo() const override;

    friend std::istream &operator>>(std::istream &is, Octagon &Octagon);
    friend std::ostream &operator<<(std::ostream &os, const Octagon &Octagon);

private:
    Point points[8];
};

class OctagonPointsCountException : public std::invalid_argument
{
public:
    OctagonPointsCountException() : std::invalid_argument("Octagon must have 8 points") {}
};

class InvalidOctagonException : public std::invalid_argument
{
public:
    InvalidOctagonException() : std::invalid_argument("Invalid Octagon") {}
};