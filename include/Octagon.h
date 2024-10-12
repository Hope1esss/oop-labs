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

    friend std::ostream &operator<<(std::ostream &os, const Octagon &Octagon);
    friend std::istream &operator>>(std::istream &is, Octagon &Octagon);

private:
    Point points[8];
    bool isOctagon() const;
};