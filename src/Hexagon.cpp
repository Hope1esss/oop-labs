#include "../include/Hexagon.h"
#include <cmath>
Hexagon::Hexagon(const Point points[6])
{
    for (int i = 0; i < 6; i++)
    {
        this->points[i] = points[i];
    }
    isValidHexagon();
}

Hexagon &Hexagon::operator=(const Hexagon &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 6; i++)
        {
            points[i] = other.points[i];
        }
    }
    return *this;
}

Hexagon &Hexagon::operator=(Hexagon &&other) noexcept
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

bool Hexagon::operator==(const Figure &other) const
{
    const Hexagon *otherHexagon = dynamic_cast<const Hexagon *>(&other);
    if (otherHexagon == nullptr)
    {
        return false;
    }
    for (int i = 0; i < 6; i++)
    {
        if (points[i].x != otherHexagon->points[i].x && points[i].y != otherHexagon->points[i].y)
        {
            return false;
        }
    }
    return true;
}

Hexagon::operator double() const
{
    double area = 0;

    for (int i = 0; i < 6; i++)
    {
        int j = (i + 1) % 6;
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }

    return std::abs(area) / 2;
}
Point Hexagon::getGeometricalCenter() const
{
    Point center;
    center.x = (points[0].x + points[1].x + points[2].x) / 6;
    center.y = (points[0].y + points[1].y + points[2].y) / 6;
    return center;
}

void Hexagon::getPointsData() const
{
    std::cout << *this << std::endl;
}

bool Hexagon::isValidHexagon() const
{
    const double epsilon = 1e-3;
    double expectedSideLength = std::sqrt(std::pow(points[1].x - points[0].x, 2) + std::pow(points[1].y - points[0].y, 2));

    for (int i = 0; i < 6; i++)
    {
        int next = (i + 1) % 6;
        double currentSideLength = std::sqrt(std::pow(points[next].x - points[i].x, 2) + std::pow(points[next].y - points[i].y, 2));

        if (std::abs(currentSideLength - expectedSideLength) > epsilon)
        {
            throw HexagonValidException();
        }
    }
    return true;
}

std::istream &operator>>(std::istream &is, Hexagon &Hexagon)
{
    Point points[6];
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
        Hexagon.points[i] = points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Hexagon &Hexagon)
{
    os << "Octagon points: ";
    for (int i = 0; i < 6; i++)
    {
        os << "(" << Hexagon.points[i].x << ", " << Hexagon.points[i].y << ") ";
    }
    return os;
}