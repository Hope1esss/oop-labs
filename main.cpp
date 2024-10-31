#include "src/Hexagon.cpp"
#include "src/Octagon.cpp"
#include "include/Point.h"
#include <iostream>

int main()
{
    Point<double> hexagonPoints[6] = {Point<double>(5, 0), Point<double>(2.5, 4.33), Point<double>(-2.5, 4.33), Point<double>(-5, 0), Point<double>(-2.5, -4.33), Point<double>(2.5, -4.33)};
    Hexagon<double> Hexagon(hexagonPoints);

    std::cout << Hexagon.getGeometricalCenter() << std::endl;

    std::cout << double(Hexagon) << std::endl;

    Point<double> octagonPoints[8] = {Point<double>(5, 0), Point<double>(3.53553, 3.53553), Point<double>(0, 5), Point<double>(-3.53553, 3.53553), Point<double>(-5, 0), Point<double>(-3.53553, -3.53553), Point<double>(0, -5), Point<double>(3.53553, -3.53553)};

    Octagon<double> Octagon(octagonPoints);

    std::cout << Octagon.getGeometricalCenter() << std::endl;

    std::cout << double(Octagon) << std::endl;

    return 0;
}