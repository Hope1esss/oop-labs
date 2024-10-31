#pragma once
#include <stdexcept>
#include <memory>
#include <iostream>
#include "../include/Figure.h"

template <Scalar T>
class Hexagon : public Figure<T>
{
public:
    Hexagon() = default;
    Hexagon(const Point<T> points[6]);
    ~Hexagon() noexcept = default;

    Hexagon &operator=(const Hexagon &other);
    Hexagon &operator=(Hexagon &&other) noexcept;

    bool operator==(const Figure<T> &other) const override;
    void getPointsData() const override;
    Point<T> getGeometricalCenter() const override;
    operator double() const override;
    bool isValidHexagon() const;

    template <Scalar S>
    friend std::istream &operator>>(std::istream &is, Hexagon<S> &hexagon);
    
    template <Scalar S>
    friend std::ostream &operator<<(std::ostream &os, const Hexagon<S> &hexagon);

private:
    std::unique_ptr<Point<T>> points[6];
};


class HexagonPointsException : public std::invalid_argument
{
public:
    HexagonPointsException() : std::invalid_argument("Invalid numbers of points for hexagon. It should be 6 points") {}
};

class HexagonValidationException : public std::invalid_argument
{
public:
    HexagonValidationException() : std::invalid_argument("Points can't form valid hexagon") {}
};