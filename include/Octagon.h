#include "../include/Figure.h"

class Octagon : public Figure
{
public:
    Octagon() = default;
    Octagon(const Point points[8]);

    Octagon &operator=(const Octagon &other);
    Octagon &operator=(Octagon &&other) noexcept;

    bool operator==(const Figure &other) const override;
    void getPointsData() const override;
    Point getGeometricalCenter() const override;
    operator double() const override;
    bool isValidOctagon() const;

    friend std::istream &operator>>(std::istream &is, Octagon &Octagon);
    friend std::ostream &operator<<(std::ostream &os, const Octagon &Octagon);

private:
    Point points[8];
};

class OctagonPointsException : public std::invalid_argument
{
public: 
    OctagonPointsException() : std::invalid_argument("Invalid numbers of points for octagon. It should be 8 points") {}
};

class OctagonValidException: public std::invalid_argument
{
    public:
    OctagonValidException() : std::invalid_argument("Points can't form valid octagon") {};
};