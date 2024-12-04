#include "../include/Octagon.h"
#include <cmath>
bool Octagon::isValid() const
{
    const double epsilon = 1e-3;
    double expectedSideLength = std::sqrt(std::pow(points[1].x - points[0].x, 2) + std::pow(points[1].y - points[0].y, 2));

    for (int i = 0; i < 8; i++)
    {
        int next = (i + 1) % 8;
        double currentSideLength = std::sqrt(std::pow(points[next].x - points[i].x, 2) + std::pow(points[next].y - points[i].y, 2));

        if (std::abs(currentSideLength - expectedSideLength) > epsilon)
        {
            throw InvalidOctagonException();
        }
    }
    return true;
}

Octagon::Octagon(const Point points[8])
{
    for (int i = 0; i < 8; i++)
    {
        this->points[i] = points[i];
    }
    isValid();
}

Octagon::operator double() const
{
    double area = std::abs(points[0].x * (points[1].y - points[2].y) + points[1].x * (points[2].y - points[0].y) + points[2].x * (points[0].y - points[1].y)) / 2.0;

    return area;
}

Point Octagon::geometricalCenter() const
{
    return Point((points[0].x + points[1].x + points[2].x) / 8.0, (points[0].y + points[1].y + points[2].y) / 8.0);
}

Octagon &Octagon::operator=(const Octagon &other)
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            points[i] = other.points[i];
        }
    }
}

Octagon &Octagon::operator=(const Octagon &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            points[i] = std::move(other.points[i]);
        }
    }
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
        if (points[i].x != otherOctagon->points[i].x || points[i].y != otherOctagon->points[i].y)
        {
            return false;
        }
    }
    return true;
}

void Octagon::printInfo() const
{
    std::cout << "Type: Octagon, Points: (" << points[0] << ", " << points[1] << ", " << points[2] << points[3] << ", " << points[4] << ", " << points[5] << ", " << points[6] << ", " << points[7] << ")" << std::endl;
}
std::istream &operator>>(std::istream &is, Octagon &Octagon)
{
    Point tempPoints[8];
    for (int i = 0; i < 8; i++)
    {
        is >> tempPoints[i];
    }
    
    if (is.fail())
    {
        throw OctagonPointsCountException();
    }
    else
    {
        return is;
    }

    for (int i = 0; i < 8; i++)
    {
        Octagon.points[i] = tempPoints[i];
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Octagon &Octagon)
{
    os << "Octagon points: ";
    for (const auto &point : Octagon.points)
    {
        os << point << " ";
    }
    return os;
}