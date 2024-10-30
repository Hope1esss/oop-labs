#include "../include/Figure.h"

class Triangle : public Figure
{
public:
    Triangle() = default;
    Triangle(const Point points[3]);

    Triangle &operator=(const Triangle &other);
    Triangle &operator=(Triangle &&other) noexcept;

    bool operator==(const Figure &other) const override;
    operator double() const override;
    Point getGeometricalCenter() const override;
    void getPointsData() const override;
    bool isValidTriangle() const;

    friend std::istream &operator>>(std::istream &is, Triangle &triangle);
    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);

private:
    Point points[3];
};

class TrianglePointsException : public std::invalid_argument
{
public:
    TrianglePointsException() : std::invalid_argument("Invalid numbers of points for triangle. It should be 3 points") {}
};

class TriangleValidException : public std::invalid_argument
{
public:
    TriangleValidException() : std::invalid_argument("Points can't form valid triangle") {}
};
