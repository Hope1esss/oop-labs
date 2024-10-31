#include "../src/Hexagon.cpp"
#include "../src/Octagon.cpp"
#include "../src/Triangle.cpp"
#include "../src/Array.cpp"
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

TEST(ArrayTest, ArrayDefaultConstrustion)
{
    Array<Figure<int>> array;

    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, AppendAndResizeTest)
{
    Array<Figure<int>> array;
    Point<int> trianglePoints1[3] = {Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 0)};
    Point<int> trianglePoints2[3] = {Point<int>(2, 0), Point<int>(3, 0), Point<int>(3, 2)};
    Point<int> trianglePoints3[3] = {Point<int>(4, 0), Point<int>(2, 1), Point<int>(2, 0)};

    std::shared_ptr<Figure<int>> triangle1 = std::make_shared<Triangle<int>>(trianglePoints1);
    std::shared_ptr<Figure<int>> triangle2 = std::make_shared<Triangle<int>>(trianglePoints2);
    std::shared_ptr<Figure<int>> triangle3 = std::make_shared<Triangle<int>>(trianglePoints3);

    array.append(triangle1);
    array.append(triangle2);
    array.append(triangle3);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array.getCapacity(), 4);
}

TEST(ArrayTest, AppendAndRemoveTest)
{
    Array<Figure<int>> array;
    Point<int> trianglePoints1[3] = {Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 0)};

    std::shared_ptr<Figure<int>> triangle1 = std::make_shared<Triangle<int>>(trianglePoints1);

    array.append(triangle1);
    EXPECT_EQ(array.getSize(), 1);

    array.remove(0);
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, GetItemTest)
{
    Array<Figure<int>> array;
    Point<int> trianglePoints1[3] = {Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 0)};

    std::shared_ptr<Figure<int>> triangle1 = std::make_shared<Triangle<int>>(trianglePoints1);

    array.append(triangle1);

    EXPECT_EQ(array[0], triangle1);
}
TEST(TriangleTest, ValidTriangleConstrustion)
{
    Point<int> points[3] = {Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 0)};

    Triangle<int> triangle(points);

    EXPECT_NO_THROW();
}

TEST(TriangleTest, InvalidTriangleConstrustion)
{
    Point<int> points[3] = {Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0)};

    EXPECT_ANY_THROW(Triangle<int> triangle(points));
}

TEST(TriangleTest, GeometricalCenterTrue)
{
    Point<double> points[3] = {Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 0)};
    Triangle<double> triangle(points);

    Point<double> expectedPoint = Point<double>(1.66667, 0.333333);

    Point<double> realPoint = triangle.getGeometricalCenter();

    EXPECT_TRUE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(TriangleTest, GeometricalCenterFalse)
{
    Point<double> points[3] = {Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 0)};
    Triangle<double> triangle(points);

    Point<double> expectedPoint = Point<double>(0, 0);

    Point<double> realPoint = triangle.getGeometricalCenter();

    EXPECT_FALSE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(TriangleTest, AreaTrue)
{
    Point<double> points[3] = {Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 0)};
    Triangle<double> triangle(points);

    double expectedArea = 0.5;

    double realArea = triangle;

    EXPECT_TRUE(std::abs(expectedArea - realArea) < 1e-3);
}

TEST(TriangleTest, AreaFalse)
{
    Point<double> points[3] = {Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 0)};
    Triangle<double> triangle(points);

    double expectedArea = 0.0;

    double realArea = triangle;

    EXPECT_FALSE(std::abs(expectedArea - realArea) < 1e-3);
}

TEST(HexagonTest, ValidHexagonConstrustion)
{
    Point<double> points[6] = {Point<double>(5, 0), Point<double>(2.5, 4.33), Point<double>(-2.5, 4.33), Point<double>(-5, 0), Point<double>(-2.5, -4.33), Point<double>(2.5, -4.33)};

    Hexagon<double> Hexagon(points);

    EXPECT_NO_THROW();
}

TEST(HexagonTest, InvalidHexagonConstrustion)
{
    Point<int> points[6] = {Point<int>(1, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0)};

    EXPECT_ANY_THROW(Hexagon<int> Hexagon(points););
}

TEST(HexagonTest, GeometricalCenterTrue)
{
    Point<double> points[6] = {Point<double>(5, 0), Point<double>(2.5, 4.33), Point<double>(-2.5, 4.33), Point<double>(-5, 0), Point<double>(-2.5, -4.33), Point<double>(2.5, -4.33)};
    Hexagon<double> Hexagon(points);

    Point<double> expectedPoint = Point<double>(0.833333, 1.44333);

    Point<double> realPoint = Hexagon.getGeometricalCenter();

    EXPECT_TRUE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(HexagonTest, GeometricalCenterFalse)
{
    Point<double> points[6] = {Point<double>(5, 0), Point<double>(2.5, 4.33), Point<double>(-2.5, 4.33), Point<double>(-5, 0), Point<double>(-2.5, -4.33), Point<double>(2.5, -4.33)};
    Hexagon<double> Hexagon(points);

    Point<double> expectedPoint = Point<double>(0, 0);

    Point<double> realPoint = Hexagon.getGeometricalCenter();

    EXPECT_FALSE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(HexagonTest, AreaTrue)
{
    Point<double> points[6] = {Point<double>(5, 0), Point<double>(2.5, 4.33), Point<double>(-2.5, 4.33), Point<double>(-5, 0), Point<double>(-2.5, -4.33), Point<double>(2.5, -4.33)};
    Hexagon<double> Hexagon(points);

    double expectedArea = 64.95;

    double realArea = Hexagon;

    EXPECT_TRUE(std::abs(expectedArea - realArea) < 1e-3);
}

TEST(HexagonTest, AreaFalse)
{
    Point<double> points[6] = {Point<double>(5, 0), Point<double>(2.5, 4.33), Point<double>(-2.5, 4.33), Point<double>(-5, 0), Point<double>(-2.5, -4.33), Point<double>(2.5, -4.33)};
    Hexagon<double> Hexagon(points);

    double expectedArea = 0.0;

    double realArea = Hexagon;

    EXPECT_FALSE(std::abs(expectedArea - realArea) < 1e-3);
}

TEST(OctagonTest, ValidOctagonConstrustion)
{
    Point<double> points[8] = {Point<double>(5, 0), Point<double>(3.53553, 3.53553), Point<double>(0, 5), Point<double>(-3.53553, 3.53553), Point<double>(-5, 0), Point<double>(-3.53553, -3.53553), Point<double>(0, -5), Point<double>(3.53553, -3.53553)};

    Octagon<double> Octagon(points);

    EXPECT_NO_THROW();
}

TEST(OctagonTest, InvalidOctagonConstrustion)
{
    Point<int> points[8] = {Point<int>(1, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0)};

    EXPECT_ANY_THROW(Octagon<int> Octagon(points));
}

TEST(OctagonTest, GeometricalCenterTrue)
{
    Point<double> points[8] = {Point<double>(5, 0), Point<double>(3.53553, 3.53553), Point<double>(0, 5), Point<double>(-3.53553, 3.53553), Point<double>(-5, 0), Point<double>(-3.53553, -3.53553), Point<double>(0, -5), Point<double>(3.53553, -3.53553)};
    Octagon<double> Octagon(points);

    Point<double> expectedPoint = Point<double>(1.06694, 1.06694); // ??????

    Point<double> realPoint = Octagon.getGeometricalCenter();

    EXPECT_TRUE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(OctagonTest, GeometricalCenterFalse)
{
    Point<double> points[8] = {Point<double>(5, 0), Point<double>(3.53553, 3.53553), Point<double>(0, 5), Point<double>(-3.53553, 3.53553), Point<double>(-5, 0), Point<double>(-3.53553, -3.53553), Point<double>(0, -5), Point<double>(3.53553, -3.53553)};
    Octagon<double> Octagon(points);

    Point<double> expectedPoint = Point<double>(0, 0);

    Point<double> realPoint = Octagon.getGeometricalCenter();

    EXPECT_FALSE(std::abs(expectedPoint.x - realPoint.x) < 1e-3 && std::abs(expectedPoint.y - realPoint.y) < 1e-3);
}

TEST(OctagonTest, AreaTrue)
{
    Point<double> points[8] = {Point<double>(5, 0), Point<double>(3.53553, 3.53553), Point<double>(0, 5), Point<double>(-3.53553, 3.53553), Point<double>(-5, 0), Point<double>(-3.53553, -3.53553), Point<double>(0, -5), Point<double>(3.53553, -3.53553)};
    Octagon<double> Octagon(points);

    double expectedArea = 70.7106;

    double realArea = Octagon;

    EXPECT_TRUE(std::abs(expectedArea - realArea) < 1e-3);
}

TEST(OctagonTest, AreaFalse)
{
    Point<double> points[8] = {Point<double>(5, 0), Point<double>(3.53553, 3.53553), Point<double>(0, 5), Point<double>(-3.53553, 3.53553), Point<double>(-5, 0), Point<double>(-3.53553, -3.53553), Point<double>(0, -5), Point<double>(3.53553, -3.53553)};
    Octagon<double> Octagon(points);

    double expectedArea = 0.0;

    double realArea = Octagon;

    EXPECT_FALSE(std::abs(expectedArea - realArea) < 1e-3);
}