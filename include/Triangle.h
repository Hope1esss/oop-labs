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

    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);
    friend std::istream &operator>>(std::istream &is, Triangle &triangle);

private:
    Point points[3];
    bool isTriangle() const;
};

class TriangleException : public std::invalid_argument
{
public:
    TriangleException() : std::invalid_argument("Invalid numbers of points for triangle. It should be 3 points") {}
};
