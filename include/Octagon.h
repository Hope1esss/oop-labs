#pragma once
#include <stdexcept>
#include <memory>
#include <iostream>
#include "../include/Figure.h"

template <Scalar T>
class Octagon : public Figure<T>
{
public:
    Octagon() = default;
    Octagon(const Point<T> points[8]);
    
    Octagon &operator=(const Octagon &other);
    Octagon &operator=(Octagon &&other) noexcept;

    bool operator==(const Figure<T> &other) const override;
    void getPointsData() const override;
    Point<T> getGeometricalCenter() const override;
    operator double() const override;
    bool isValidOctagon() const;
    
    template <Scalar S>
    friend std::istream &operator>>(std::istream &is, Octagon<S> &octagon);

    template <Scalar S>
    friend std::ostream &operator<<(std::ostream &os, const Octagon<S> &octagon);

    ~Octagon() noexcept = default;

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