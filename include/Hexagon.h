#pragma once
#include "Figure.h"

class Hexagon : public Figure
{
public:
    Hexagon() = default;
    Hexagon(const Point points[3]);

    operator double() const override;
    Point geometricalCenter() const override;
    
    Hexagon &operator=(const Hexagon &other);
    Hexagon &operator=(const Hexagon &&other) noexcept;
    bool operator==(const Figure &other) const override;

    bool isValid() const;
    void printInfo() const override;

    friend std::istream &operator>>(std::istream &is, Hexagon &Hexagon);
    friend std::ostream &operator<<(std::ostream &os, const Hexagon &Hexagon);

private:
    Point points[6];
};

class HexagonPointsCountException : public std::invalid_argument
{
public:
    HexagonPointsCountException() : std::invalid_argument("Hexagon must have 6 points") {}
};

class InvalidHexagonException : public std::invalid_argument
{
public:
    InvalidHexagonException() : std::invalid_argument("Invalid Hexagon") {}
};