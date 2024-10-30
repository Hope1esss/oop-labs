#pragma once
#include "../include/Figure.h"

template <Scalar T>
class Octagon : public Figure<T>
{
public:
    Octagon() = default;
    Octagon(const Point<T> points[8]);

    Octagon &operator=(const Octagon &other);
    Octagon &operator=(Octagon &&other) noexcept;

    bool operator==(const Figure &other) const override;
    void getPointsData() const override;
    Point<T> getGeometricalCenter() const override;
    operator double() const override;
    bool isValidOctagon() const;

    friend std::istream &operator>>(std::istream &is, Octagon<T> &Octagon);
    friend std::ostream &operator<<(std::ostream &os, const Octagon<T> &Octagon);

private:
    std::unique_ptr<Point<T>> points[8];
};

class OctagonPointsException : public std::invalid_argument
{
public:
    OctagonPointsException() : std::invalid_argument("Invalid numbers of points for octagon. It should be 8 points") {}
};

class OctagonValidationException : public std::invalid_argument
{
public:
    OctagonValidationException() : std::invalid_argument("Points can't form valid octagon") {};
};