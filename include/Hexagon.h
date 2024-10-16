#include "../include/Figure.h"

class Hexagon : public Figure
{
public:
    Hexagon() = default;
    Hexagon(const Point points[6]);

    Hexagon &operator=(const Hexagon &other);
    Hexagon &operator=(Hexagon &&other) noexcept;

    bool operator==(const Figure &other) const override;
    void getPointsData() const override;
    Point getGeometricalCenter() const override;
    operator double() const override;
    bool isValidHexagon() const;

    friend std::istream &operator>>(std::istream &is, Hexagon &Hexagon);    
    friend std::ostream &operator<<(std::ostream &os, const Hexagon &Hexagon);

private:
    Point points[6];
};

class HexagonPointsException : public std::invalid_argument
{
public:
HexagonPointsException() : std::invalid_argument("Invalid numbers of points for hexagon. It should be 6 points") {}
};

class HexagonValidException : public std::invalid_argument
{
public:
HexagonValidException() : std::invalid_argument("Points can't form valid hexagon") {}
};