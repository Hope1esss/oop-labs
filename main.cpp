#include <iostream>
#include "src/Array.cpp"
#include "src/Triangle.cpp"
#include "src/Hexagon.cpp"
#include "src/Octagon.cpp"
#include "include/Point.h"

void showMenu()
{
    std::cout << "Choose one of the following:" << std::endl;
    std::cout << "1. Add Figure" << std::endl;
    std::cout << "2. Remove Figure" << std::endl;
    std::cout << "3. Calculate total area of figures" << std::endl;
    std::cout << "4. Calculate geometrical center of figure" << std::endl;
    std::cout << "5. Print all figures" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

std::shared_ptr<Figure<double>> addFigure()
{
    int figureChoise = 0;
    std::cout << "Choose a figure you want to add in array:" << std::endl;
    std::cout << "1. Triangle" << std::endl;
    std::cout << "2. Hexagon" << std::endl;
    std::cout << "3. Octagon" << std::endl;
    std::cin >> figureChoise;

    switch (figureChoise)
    {
    case 1:
    {
        Point<double> points[3];
        std::cout << "Enter 3 points of the triangle. Example: 'x y':" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }
        std::shared_ptr<Figure<double>> triangle = std::make_shared<Triangle<double>>(points);

        return triangle;
    }

    case 2:
    {
        Point<double> points[6];
        std::cout << "Enter 6 points of the hexagon. Example: 'x y':" << std::endl;
        for (int i = 0; i < 6; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }
        std::shared_ptr<Figure<double>> hexagon = std::make_shared<Hexagon<double>>(points);

        return hexagon;
    }

    case 3:
    {
        Point<double> points[8];
        std::cout << "Enter 8 points of the octagon. Example: 'x y':" << std::endl;
        for (int i = 0; i < 8; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }
        std::shared_ptr<Figure<double>> octagon = std::make_shared<Octagon<double>>(points);

        return octagon;
    }
    default:
        std::cout << "Invalid input. Choose 1, 2 or 3" << std::endl;
        break;
    }
    return nullptr;
}

int main()
{
    std::cout << "Welcome to Figures program" << std::endl;
    Array<Figure<double>> array;
    int figuresCount = 0;
    int choise = 0;

    while (choise != 6)
    {
        showMenu();
        if (!(std::cin >> choise))
        {
            std::cerr << "Invalid Input. Enter number from 1 to 6" << std::endl;
            std::cin.clear();
            continue;
        }

        try
        {
            switch (choise)
            {
            case 1:
            {
                std::shared_ptr<Figure<double>> figure = addFigure();
                if (figure != nullptr)
                {
                    array.append(figure);
                    figuresCount++;
                    std::cout << "Figure successfully added" << std::endl;
                }
                break;
            }
            case 2:
            {
                if(figuresCount == 0)
                {
                    std::cout << "Array is empty, can't delete figure" << std::endl;
                    break;
                }

                std::cout << "Size of array is " << figuresCount << std::endl;
                std::cout << "Enter index of figure you want to delete:" << std::endl;
                int index;
                std::cin >> index;
                if (index < 0 || index >= figuresCount)
                {
                    std::cout << "Invalid index" << std::endl;
                    break;
                }
                array.remove(index);
                figuresCount--;
                std::cout << "Figure successfully deleted" << std::endl;
                break;
            }
            case 3:
            {
                if (figuresCount == 0)
                {
                    std::cout << "Array is empty, can't calculate total area" << std::endl;
                    break;
                }
                double totalArea = array.calculateTotalArea();
                std::cout << "Total area is " << totalArea << std::endl;
                break;
            }

            case 4:
            {
                if (figuresCount == 0)
                {
                    std::cout << "Array is empty, can't calculate geometrical center" << std::endl;
                    break;
                }

                std::cout << "Size of array is " << figuresCount << std::endl;
                std::cout << "Enter index of figure you want to calculate geometrical center:" << std::endl;
                int index;
                std::cin >> index;
                if (index < 0 || index >= figuresCount)
                {
                    std::cout << "Invalid index" << std::endl;
                    break;
                }

                Point<double> center = array[index]->getGeometricalCenter();
                std::cout << "Geometrical center is (" << center.x << ", " << center.y << ")" <<std::endl;
                break;
            }

            case 5:
            {
                if (figuresCount == 0)
                {
                    std::cout << "Array is empty" << std::endl;
                    break;
                }

                for (int i = 0; i < figuresCount; i++)
                {
                    array[i]->getPointsData();
                    std::cout << std::endl;
                }
                break;
            }

            case 6:
            {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default:
            std::cout << "Invalid Option" << std::endl;
            break;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}