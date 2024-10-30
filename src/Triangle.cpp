#include "../include/Triangle.h"
#include <cmath>

Triangle::Triangle(const Point points[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->points[i] = points[i];
    }

    isValidTriangle();
}

Triangle &Triangle::operator=(const Triangle &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 3; i++)
        {
            points[i] = other.points[i];
        }
    }
    return *this;
}

Triangle &Triangle::operator=(Triangle &&other) noexcept
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

bool Triangle::operator==(const Figure &other) const
{
    const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
    if (otherTriangle == nullptr)
    {
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        if (points[i].x != otherTriangle->points[i].x && points[i].y != otherTriangle->points[i].y)
        {
            return false;
        }
    }

    return true;
}

Triangle::operator double() const
{
    double area = 0.5 * std::abs(points[0].x * (points[1].y - points[2].y) + points[1].x * (points[2].y - points[0].y) + points[2].x * (points[0].y - points[1].y));

    return area;
}

Point Triangle::getGeometricalCenter() const
{
    Point center;
    center.x = (points[0].x + points[1].x + points[2].x) / 3;
    center.y = (points[0].y + points[1].y + points[2].y) / 3;
    return center;
}

void Triangle::getPointsData() const
{
    std::cout << *this << std::endl;
}

bool Triangle::isValidTriangle() const
{
    double side1 = std::sqrt(std::pow(points[1].x - points[0].x, 2) + std::pow(points[1].y - points[0].y, 2));
    double side2 = std::sqrt(std::pow(points[2].x - points[1].x, 2) + std::pow(points[2].y - points[1].y, 2));
    double side3 = std::sqrt(std::pow(points[2].x - points[0].x, 2) + std::pow(points[2].y - points[0].y, 2));
    if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1)
    {
        return true;
    }
    throw TriangleValidException();
}

std::istream &operator>>(std::istream &is, Triangle &triangle)
{
    Point points[3];
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
        triangle.points[i] = points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Triangle &triangle)
{
    os << "Triangle points: ";
    for (int i = 0; i < 3; i++)
    {
        os << "(" << triangle.points[i].x << ", " << triangle.points[i].y << ") ";
    }
    return os;
}
