#include <iostream>
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/Triangle.h"
void showMenu()
{
    std::cout << "Choose one of the following:" << std::endl;
    std::cout << "1. Add Figure" << std::endl;
    std::cout << "2. Delete Figure" << std::endl;
    std::cout << "3. Calculate total area" << std::endl;
    std::cout << "4. Calculate geometrical center of fugure" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

Figure *addFigure()
{
    int choise = 0;
    std::cout << "Choose type of the figure: " << std::endl;
    std::cout << "1. Triangle" << std::endl;
    std::cout << "2. Hexagon" << std::endl;
    std::cout << "3. Octagon" << std::endl;
    std::cin >> choise;

    switch (choise)
    {
    case 1:
    {
        Point points[3];
        std::cout << "Enter 3 points of the triangle in order. Example: 'x y': " << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }
        return new Triangle(points);
    }
    case 2:
    {
        Point points[6];
        std::cout << "Enter 6 points of the hexagon in order. Example: 'x y': " << std::endl;
        for (int i = 0; i < 6; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }
        return new Hexagon(points);
    }
    case 3:
    {
        Point points[8];
        std::cout << "Enter 8 points of the octagon in order. Example: 'x y': " << std::endl;
        for (int i = 0; i < 8; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }
        return new Octagon(points);
    }
    default:
        std::cout << "Invalid input. Choose 1, 2 or 3" << std::endl;
        break;
    }
    return nullptr;
}
int main()
{
    std::cout << "Welcome to Figures Program" << std::endl;
    int arraySize;
    std::cout << "Let's create array for figures. Enter size of it: ";
    std::cin >> arraySize;

    Figure *figuresArray[arraySize];
    int figureCount = 0;
    int choise = 0;
    while (choise != 5)
    {
        showMenu();
        if (!(std::cin >> choise))
        {
            std::cerr << "Invalid input. Enter number from 1 to 5" << std::endl;
            std::cin.clear();
            continue;
        }

        try
        {
            switch (choise)
            {
            case 1:
            {
                if (figureCount >= arraySize)
                {
                    std::cout << "Array is full, can't add figure" << std::endl;
                    break;
                }
                Figure *figure = addFigure();
                if (figure != nullptr)
                {
                    figuresArray[figureCount] = figure;
                    figureCount++;
                }
                break;
            }
            case 2:
            {
                if (figureCount == 0)
                {
                    std::cout << "Array is empty, can't delete figure" << std::endl;
                    break;
                }
                std::cout << "Size of array is " << figureCount << std::endl;
                std::cout << "Enter index of figure to delete: ";
                int index;
                std::cin >> index;
                if (index < 0 || index >= figureCount)
                {
                    std::cout << "Invalid index" << std::endl;
                    break;
                }
                delete figuresArray[index];
                for (int i = index; i < figureCount - 1; i++)
                {
                    figuresArray[i] = figuresArray[i + 1];
                }
                figureCount--;
                std::cout << "Figure successfully deleted" << std::endl;
                break;
            }
            case 3:
            {
                double totalArea = 0;
                for (int i = 0; i < figureCount; i++) {
                    totalArea += static_cast<double>(*figuresArray[i]);
                }
                std::cout << "Total area is " << totalArea << std::endl;
                break;
            }
            case 4:
            {
                if (figureCount == 0)
                {
                    std::cout << "Array is empty, can't calculate geometrical center" << std::endl;
                    break;
                }
                std::cout << "Size of array is " << figureCount << std::endl;
                std::cout << "Enter index of figure to calculate geometrical center: ";
                int index;
                std::cin >> index;
                if (index < 0 || index >= figureCount)
                {
                    std::cout << "Invalid index" << std::endl;
                    break;
                }
                std::cout << "Geometrical center is " << figuresArray[index]->getGeometricalCenter() << std::endl;
                break;
            }
            case 5:
            {
                std::cout << "Goodbye!" << std::endl;
                for (int i = 0; i < figureCount; i++)
                {
                    delete figuresArray[i];
                }
                return 0;
            }
            default:
            std::cout << "Invalid option" << std::endl;
            break;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

    }
    return 0;
}