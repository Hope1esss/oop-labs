#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(TriangleTest, ValidTriangleConstruction)
{
    Point points[3] = {{1, 0}, {2, 1}, {2, 0}};

    ASSERT_NO_THROW(Triangle triangle(points));
}

TEST(TriangleTest, InvalidTriangleConstruction)
{
    Point points[3] = {{0, 0}, {0, 0}, {0, 0}};

    ASSERT_ANY_THROW(Triangle triangle(points));
}

TEST(TriangleTest, GeometricalCenterTrue)
{
    Point points[3] = {{1, 0}, {2, 1}, {2, 0}};
    Triangle triangle(points);
    Point expectedPoint = {1.66667, 0.333333};

    Point realPoint = triangle.getGeometricalCenter();

    ASSERT_TRUE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(TriangleTest, GeometricalCenterFalse)
{
    Point points[3] = {{1, 0}, {2, 1}, {2, 0}};
    Triangle triangle(points);
    Point expectedPoint = {0, 0};

    Point realPoint = triangle.getGeometricalCenter();

    ASSERT_FALSE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(HexagonTest, ValidHexagonConstruction)
{
    Point points[6] = {{5, 0}, {2.5, 4.33}, {-2.5, 4.33}, {-5, 0}, {-2.5, -4.33}, {2.5, -4.33}};

    ASSERT_NO_THROW(Hexagon hexagon(points));
}

TEST(HexagonText, InvalidHexagonConstruction)
{
    Point points[6] = {{1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    ASSERT_ANY_THROW(Hexagon hexagon(points));
}

TEST(HexagonTest, GeometricalCenterTrue)
{
    Point points[6] = {{5, 0}, {2.5, 4.33}, {-2.5, 4.33}, {-5, 0}, {-2.5, -4.33}, {2.5, -4.33}};
    Hexagon hexagon(points);
    Point expectedPoint = {0.833333, 1.44333};

    Point realPoint = hexagon.getGeometricalCenter();

    ASSERT_TRUE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(HexagonTest, GeometricalCenterFalse)
{
    Point points[6] = {{5, 0}, {2.5, 4.33}, {-2.5, 4.33}, {-5, 0}, {-2.5, -4.33}, {2.5, -4.33}};
    Hexagon hexagon(points);
    Point expectedPoint = {0, 0};

    Point realPoint = hexagon.getGeometricalCenter();

    ASSERT_FALSE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(OctagonText, ValidOctagonConstruction)
{
    Point points[8] = {{5, 0}, {3.53553, 3.53553}, {0, 5}, {-3.53553, 3.53553}, {-5, 0}, {-3.53553, -3.53553}, {0, -5}, {3.53553, -3.53553}}
;

    ASSERT_NO_THROW(Octagon octagon(points));
}

TEST(OctagonText, InvalidOctagonConstruction)
{
    Point points[8] = {{1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    ASSERT_ANY_THROW(Octagon octagon(points));
}

TEST(OctagonTest, GeometricalCenterTrue)
{
    Point points[8] = {{5, 0}, {3.53553, 3.53553}, {0, 5}, {-3.53553, 3.53553}, {-5, 0}, {-3.53553, -3.53553}, {0, -5}, {3.53553, -3.53553}};
    Octagon octagon(points);
    Point expectedPoint = {1.06694, 1.06694};

    Point realPoint = octagon.getGeometricalCenter();

    ASSERT_TRUE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);

}

TEST(OctagonTest, GeometricalCenterFalse)
{
    Point points[8] = {{5, 0}, {3.53553, 3.53553}, {0, 5}, {-3.53553, 3.53553}, {-5, 0}, {-3.53553, -3.53553}, {0, -5}, {3.53553, -3.53553}};
    Octagon octagon(points);
    Point expectedPoint = {0, 0};

    Point realPoint = octagon.getGeometricalCenter();

    ASSERT_FALSE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}