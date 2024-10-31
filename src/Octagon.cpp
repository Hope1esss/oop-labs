#include "../include/Octagon.h"
#include <cmath>
#include <memory>

template <Scalar T>
Octagon<T>::Octagon(const Point<T> points[8])
{
    for (int i = 0; i < 8; i++)
    {
        this->points[i] = std::make_unique<Point<T>>(points[i]);
    }

    isValidOctagon();
}

template <Scalar T>
Octagon<T> &Octagon<T>::operator=(const Octagon<T> &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 8; i++)
        {
            points[i] = std::make_unique<Point<T>>(other.points[i]);
        }
    }

    return *this;
}

template <Scalar T>
Octagon<T> &Octagon<T>::operator=(Octagon<T> &&other) noexcept
{
    if (this != &other)
    {
        for (int i = 0; i < 8; i++)
        {
            points[i] = std::move(other.points[i]);
        }
    }

    return *this;
}

template <Scalar T>
bool Octagon<T>::operator==(const Figure<T> &other) const
{
    const Octagon *otherOctagon = dynamic_cast<const Octagon *>(&other);
    if (otherOctagon == nullptr)
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        if (points[i]->x != otherOctagon->points[i]->x || points[i]->y != otherOctagon->points[i]->y)
        {
            return false;
        }
    }

    return true;
}

template <Scalar T>
Octagon<T>::operator double() const
{
    double area = 0;

    for (int i = 0; i < 8; i++)
    {
        int j = (i + 1) % 8;
        area += points[i]->x * points[j]->y - points[j]->x * points[i]->y;
    }

    return std::abs(area) / 2;
}

template <Scalar T>
Point<T> Octagon<T>::getGeometricalCenter() const
{
    Point<T> center;
    center.x = (points[0]->x + points[1]->x + points[2]->x) / 8;
    center.y = (points[0]->y + points[1]->y + points[2]->y) / 8;
    return center;
}

template <Scalar T>
void Octagon<T>::getPointsData() const
{
    std::cout << *this << std::endl;
}

template <Scalar T>
bool Octagon<T>::isValidOctagon() const
{
    const double epsilon = 1e-3;
    double expectedSideLength = std::sqrt(std::pow(points[1]->x - points[0]->x, 2) + std::pow(points[1]->y - points[0]->y, 2));

    for (int i = 0; i < 8; i++)
    {
        int next = (i + 1) % 8;
        double currentSideLength = std::sqrt(std::pow(points[next]->x - points[i]->x, 2) + std::pow(points[next]->y - points[i]->y, 2));

        if (std::abs(currentSideLength - expectedSideLength) > epsilon)
        {
            throw OctagonValidationException();
        }
    }
    return true;
}

template <Scalar T>
std::istream &operator>>(std::istream &is, Octagon<T> &octagon)
{
    Point<T> points[8];

    for (int i = 0; i < 8; i++)
    {
        is >> points[i];
    }

    if (is.fail())
    {
        throw OctagonPointsException();
    }

    for (int i = 0; i < 8; i++)
    {
        octagon.points[i] = std::make_unique<Point<T>>(points[i]);
    }

    return is;
}

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Octagon<T> &octagon)
{
    os << "Octagon points: ";
    for (int i = 0; i < 8; i++)
    {
        os << "(" << octagon.points[i]->x << ", " << octagon.points[i]->y << ") ";
    }
    return os;
}