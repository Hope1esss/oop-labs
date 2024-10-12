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

    friend std::ostream &operator<<(std::ostream &os, const Hexagon &Hexagon);
    friend std::istream &operator>>(std::istream &is, Hexagon &Hexagon);

private:
    Point points[6];
    bool isHexagon() const;
};