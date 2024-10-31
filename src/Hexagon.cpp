#include "../include/Hexagon.h"
#include <cmath>
#include <memory>

template <Scalar T>
Hexagon<T>::Hexagon(const Point<T> points[6])
{
    for (int i = 0; i < 6; i++)
    {
        this->points[i] = std::make_unique<Point<T>>(points[i]);
    }

    isValidHexagon();
}

template <Scalar T>
Hexagon<T> &Hexagon<T>::operator=(const Hexagon<T> &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 6; i++)
        {
            points[i] = std::make_unique<Point<T>>(other.points[i]);
        }
    }

    return *this;
}

template <Scalar T>
Hexagon<T> &Hexagon<T>::operator=(Hexagon<T> &&other) noexcept
{
    if (this != &other)
    {
        for (int i = 0; i < 6; i++)
        {
            points[i] = std::move(other.points[i]);
        }
    }

    return *this;
}

template <Scalar T>
bool Hexagon<T>::operator==(const Figure<T> &other) const
{
    const Hexagon *otherHexagon = dynamic_cast<const Hexagon *>(&other);
    if (otherHexagon == nullptr)
    {
        return false;
    }

    for (int i = 0; i < 6; i++)
    {
        if (points[i]->x != otherHexagon->points[i]->x || points[i]->y != otherHexagon->points[i]->y)
        {
            return false;
        }
    }

    return true;
}

template <Scalar T>
Hexagon<T>::operator double() const
{
    double area = 0;

    for (int i = 0; i < 6; i++)
    {
        int j = (i + 1) % 6;
        area += points[i]->x * points[j]->y - points[j]->x * points[i]->y;
    }

    return std::abs(area) / 2;
}

template <Scalar T>
Point<T> Hexagon<T>::getGeometricalCenter() const
{
    Point<T> center;
    center.x = (points[0]->x + points[1]->x + points[2]->x) / 6;
    center.y = (points[0]->y + points[1]->y + points[2]->y) / 6;
    return center;
}

template <Scalar T>
void Hexagon<T>::getPointsData() const
{
    std::cout << *this << std::endl;
}

template <Scalar T>
bool Hexagon<T>::isValidHexagon() const
{
    const double epsilon = 1e-3;
    double expectedSideLength = std::sqrt(std::pow(points[1]->x - points[0]->x, 2) + std::pow(points[1]->y - points[0]->y, 2));

    for (int i = 0; i < 6; i++)
    {
        int next = (i + 1) % 6;
        double currentSideLength = std::sqrt(std::pow(points[next]->x - points[i]->x, 2) + std::pow(points[next]->y - points[i]->y, 2));

        if (std::abs(currentSideLength - expectedSideLength) > epsilon)
        {
            throw HexagonValidationException();
        }
    }
    return true;
}

template <Scalar T>
std::istream &operator>>(std::istream &is, Hexagon<T> &hexagon)
{
    Point<T> points[6];

    for (int i = 0; i < 6; i++)
    {
        is >> points[i];
    }

    if (is.fail())
    {
        throw HexagonPointsException();
    }

    for (int i = 0; i < 6; i++)
    {
        hexagon.points[i] = std::make_unique<Point<T>>(points[i]);
    }

    return is;
}

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Hexagon<T> &hexagon)
{
    os << "Hexagon points: ";
    for (int i = 0; i < 6; i++)
    {
        os << "(" << hexagon.points[i]->x << ", " << hexagon.points[i]->y << ") ";
    }
    return os;
}