#include "../include/Hexagon.h"
#include <cmath>
bool Hexagon::isValid() const
{
    const double epsilon = 1e-3;
    double expectedSideLength = std::sqrt(std::pow(points[1].x - points[0].x, 2) + std::pow(points[1].y - points[0].y, 2));

    for (int i = 0; i < 6; i++)
    {
        int next = (i + 1) % 6;
        double currentSideLength = std::sqrt(std::pow(points[next].x - points[i].x, 2) + std::pow(points[next].y - points[i].y, 2));

        if (std::abs(currentSideLength - expectedSideLength) > epsilon)
        {
            throw InvalidHexagonException();
        }
    }
    return true;
}

Hexagon::Hexagon(const Point points[6])
{
    for (int i = 0; i < 6; i++)
    {
        this->points[i] = points[i];
    }
    isValid();
}

Hexagon::operator double() const
{
    double area = std::abs(points[0].x * (points[1].y - points[2].y) + points[1].x * (points[2].y - points[0].y) + points[2].x * (points[0].y - points[1].y)) / 2.0;

    return area;
}

Point Hexagon::geometricalCenter() const
{
    return Point((points[0].x + points[1].x + points[2].x) / 6.0, (points[0].y + points[1].y + points[2].y) / 6.0);
}

Hexagon &Hexagon::operator=(const Hexagon &other)
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            points[i] = other.points[i];
        }
    }
}

Hexagon &Hexagon::operator=(const Hexagon &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            points[i] = std::move(other.points[i]);
        }
    }
}

bool Hexagon::operator==(const Figure &other) const
{
    const Hexagon *otherHexagon = dynamic_cast<const Hexagon *>(&other);
    if (otherHexagon == nullptr)
    {
        return false;
    }
    for (int i = 0; i < 8; i++)
    {
        if (points[i].x != otherHexagon->points[i].x || points[i].y != otherHexagon->points[i].y)
        {
            return false;
        }
    }
    return true;
}

void Hexagon::printInfo() const
{
    std::cout << "Type: Hexagon, Points: (" << points[0] << ", " << points[1] << ", " << points[2] << ", " << points[3] << ", " << points[4] << ", " << points[5] << ")" << std::endl;
}
std::istream &operator>>(std::istream &is, Hexagon &Hexagon)
{
    Point tempPoints[6];
    for (int i = 0; i < 6; i++)
    {
        is >> tempPoints[i];
    }

    if (is.fail())
    {
        throw HexagonPointsCountException();
    }
    else
    {
        return is;
    }

    for (int i = 0; i < 6; i++)
    {
        Hexagon.points[i] = tempPoints[i];
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Hexagon &Hexagon)
{
    os << "Hexagon points: ";
    for (const auto &point : Hexagon.points)
    {
        os << point << " ";
    }
    return os;
}