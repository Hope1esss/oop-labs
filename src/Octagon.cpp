#include "../include/Octagon.h"
#include <cmath>
Octagon::Octagon(const Point points[8])
{
    for (int i = 0; i < 8; i++)
    {
        this->points[i] = points[i];
    }
    isValidOctagon();
}

Octagon &Octagon::operator=(const Octagon &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 8; i++)
        {
            points[i] = other.points[i];
        }
    }
    return *this;
}

Octagon &Octagon::operator=(Octagon &&other) noexcept
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

bool Octagon::operator==(const Figure &other) const
{
    const Octagon *otherOctagon = dynamic_cast<const Octagon *>(&other);
    if (otherOctagon == nullptr)
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        if (points[i].x != otherOctagon->points[i].x && points[i].y != otherOctagon->points[i].y)
        {
            return false;
        }
    }
    return true;
}

Octagon::operator double() const
{
    double area = 0;

    for (int i = 0; i < 8; i++)
    {
        int j = (i + 1) % 8;
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }

    return std::abs(area) / 2;
}
Point Octagon::getGeometricalCenter() const
{
    Point center;
    center.x = (points[0].x + points[1].x + points[2].x) / 8;
    center.y = (points[0].y + points[1].y + points[2].y) / 8;
    return center;
}

void Octagon::getPointsData() const
{
    std::cout << *this << std::endl;
}

bool Octagon::isValidOctagon() const
{
    const double epsilon = 1e-3;
    double expectedSideLength = std::sqrt(std::pow(points[1].x - points[0].x, 2) + std::pow(points[1].y - points[0].y, 2));

    for (int i = 0; i < 8; i++)
    {
        int next = (i + 1) % 8;
        double currentSideLength = std::sqrt(std::pow(points[next].x - points[i].x, 2) + std::pow(points[next].y - points[i].y, 2));

        if (std::abs(currentSideLength - expectedSideLength) > epsilon)
        {
            throw OctagonValidException();
        }
    }
    return true;
}

std::istream &operator>>(std::istream &is, Octagon &Octagon)
{
    Point points[8];
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
        Octagon.points[i] = points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Octagon &Octagon)
{
    os << "Octagon points: ";
    for (int i = 0; i < 8; i++)
    {
        os << "(" << Octagon.points[i].x << ", " << Octagon.points[i].y << ") ";
    }
    return os;
}
