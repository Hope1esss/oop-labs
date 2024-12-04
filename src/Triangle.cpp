#include "../include/Triangle.h"
#include <cmath>
bool Triangle::isValid() const
{
    double side1 = std::sqrt(std::pow(points[1].x - points[0].x, 2) + std::pow(points[1].y - points[0].y, 2));
    double side2 = std::sqrt(std::pow(points[2].x - points[1].x, 2) + std::pow(points[2].y - points[1].y, 2));
    double side3 = std::sqrt(std::pow(points[2].x - points[0].x, 2) + std::pow(points[2].y - points[0].y, 2));
    if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1)
    {
        return true;
    }
    throw InvalidTriangleException();
}

Triangle::Triangle(const Point points[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->points[i] = points[i];
    }
    isValid();
}

Triangle::operator double() const
{
    double area = std::abs(points[0].x * (points[1].y - points[2].y) + points[1].x * (points[2].y - points[0].y) + points[2].x * (points[0].y - points[1].y)) / 2.0;

    return area;
}

Point Triangle::geometricalCenter() const
{
    return Point((points[0].x + points[1].x + points[2].x) / 3.0, (points[0].y + points[1].y + points[2].y) / 3.0);
}

Triangle &Triangle::operator=(const Triangle &other)
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            points[i] = other.points[i];
        }
    }
}

Triangle &Triangle::operator=(const Triangle &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            points[i] = std::move(other.points[i]);
        }
    }
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
        if (points[i].x != otherTriangle->points[i].x || points[i].y != otherTriangle->points[i].y)
        {
            return false;
        }
    }
    return true;
}

void Triangle::printInfo() const
{
    std::cout << "Type: Triangle, Points: (" << points[0] << ", " << points[1] << ", " << points[2] << ")" << std::endl;
}

std::istream &operator>>(std::istream &is, Triangle &triangle)
{
    Point tempPoints[3];
    for (int i = 0; i < 3; i++)
    {
        is >> tempPoints[i];
    }

    if (is.fail())
    {
        throw TrianglePointsCountException();
    }
    else
    {
        return is;
    }

    for (int i = 0; i < 3; i++)
    {
        triangle.points[i] = tempPoints[i];
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Triangle &triangle)
{
    os << "Triangle points: ";
    for (const auto &point : triangle.points)
    {
        os << point << " ";
    }
    return os;
}