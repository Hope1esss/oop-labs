#pragma once
#include "../include/Figure.h"

template <Scalar T>
class Hexagon : public Figure<T>
{
public:
    Hexagon() = default;
    Hexagon(const Point<T> points[6]);

    Hexagon &operator=(const Hexagon &other);
    Hexagon &operator=(Hexagon &&other) noexcept;

    bool operator==(const Figure &other) const override;
    void getPointsData() const override;
    Point<T> getGeometricalCenter() const override;
    operator double() const override;
    bool isValidHexagon() const;

    friend std::istream &operator>>(std::istream &is, Hexagon<T> &Hexagon);    
    friend std::ostream &operator<<(std::ostream &os, const Hexagon<T> &Hexagon);

private:
    std::unique_ptr<Point<T>> points[6];
};

class HexagonPointsException : public std::invalid_argument
{
public:
HexagonPointsException() : std::invalid_argument("Invalid numbers of points for hexagon. It should be 6 points") {}
};

class HexagonValidException : public std::invalid_argument
{
public:
HexagonValidException() : std::invalid_argument("Points can't form valid hexagon") {}
};