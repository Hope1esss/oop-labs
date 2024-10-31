#include "../include/Triangle.h"
#include <cmath>
#include <memory>

template <Scalar T>
Triangle<T>::Triangle(const Point<T> points[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->points[i] = std::make_unique<Point<T>>(points[i]);
    }

    isValidTriangle();
}

template <Scalar T>
Triangle<T> &Triangle<T>::operator=(const Triangle<T> &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 3; i++)
        {
            points[i] = std::make_unique<Point<T>>(other.points[i]);
        }
    }

    return *this;
}

template <Scalar T>
Triangle<T> &Triangle<T>::operator=(Triangle<T> &&other) noexcept
{
    if (this != &other)
    {
        for (int i = 0; i < 3; i++)
        {
            points[i] = std::move(other.points[i]);
        }
    }

    return *this;
}

template <Scalar T>
bool Triangle<T>::operator==(const Figure<T> &other) const
{
    const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
    if (otherTriangle == nullptr)
    {
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        if (points[i]->x != otherTriangle->points[i]->x || points[i]->y != otherTriangle->points[i]->y)
        {
            return false;
        }
    }

    return true;
}

template <Scalar T>
Triangle<T>::operator double() const
{
    double area = 0.5 * std::abs(points[0]->x * (points[1]->y - points[2]->y) + points[1]->x * (points[2]->y - points[0]->y) + points[2]->x * (points[0]->y - points[1]->y));

    return area;
}

template <Scalar T>
Point<T> Triangle<T>::getGeometricalCenter() const
{
    Point<T> center;
    center.x = (points[0]->x + points[1]->x + points[2]->x) / 3;
    center.y = (points[0]->y + points[1]->y + points[2]->y) / 3;
    return center;
}

template <Scalar T>
void Triangle<T>::getPointsData() const
{
    std::cout << *this << std::endl;
}

template <Scalar T>
bool Triangle<T>::isValidTriangle() const
{
    double side1 = std::sqrt(std::pow(points[1]->x - points[0]->x, 2) + std::pow(points[1]->y - points[0]->y, 2));
    double side2 = std::sqrt(std::pow(points[2]->x - points[1]->x, 2) + std::pow(points[2]->y - points[1]->y, 2));
    double side3 = std::sqrt(std::pow(points[2]->x - points[0]->x, 2) + std::pow(points[2]->y - points[0]->y, 2));

    if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1)
    {
        return true;
    }

    throw TriangleValidationException();
}

template <Scalar T>
std::istream &operator>>(std::istream &is, Triangle<T> &triangle)
{
    Point<T> points[3];

    for (int i = 0; i < 3; i++)
    {
        is >> points[i];
    }

    if (is.fail())
    {
        throw TrianglePointsException();
    }

    for (int i = 0; i < 3; i++)
    {
        triangle.points[i] = std::make_unique<Point<T>>(points[i]);
    }

    return is;
}

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Triangle<T> &triangle)
{
    os << "Triangle points: ";
    for (int i = 0; i < 3; i++)
    {
        os << "(" << triangle.points[i]->x << ", " << triangle.points[i]->y << ") ";
    }
    return os;
}