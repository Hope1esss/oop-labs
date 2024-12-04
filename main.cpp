#include <iostream>
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/Triangle.h"

void showMenu()
{
    std::cout << "---Figures Menu---" << std::endl;
    std::cout << "1. Add Figure" << std::endl;
    std::cout << "2. Remove Figure" << std::endl;
    std::cout << "3. Print All Figures" << std::endl;
    std::cout << "4. Get Geometrical Center of Figure" << std::endl;
    std::cout << "5. Get Area of Figure" << std::endl;
    std::cout << "6. Get Area of All Figures" << std::endl;
    std::cout << "7. Resize figures array" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

Figure *addFigure()
{
    int choise = 0;
    std::cout << "Choose Figure: " << std::endl;
    std::cout << "1. Triangle" << std::endl;
    std::cout << "2. Hexagon" << std::endl;
    std::cout << "3. Octagon" << std::endl;
    std::cin >> choise;

    switch (choise)
    {
    case 1:
    {
        Point points[3];
        std::cout << "Enter points in order (example: <x y>):" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }

        return new Triangle(points);
    }

    case 2:
    {
        Point points[6];
        std::cout << "Enter points in order (example: <x y>):" << std::endl;
        for (int i = 0; i < 6; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }

        return new Hexagon(points);
    }

    case 3:
    {
        Point points[8];
        std::cout << "Enter points in order (example: <x y>):" << std::endl;
        for (int i = 0; i < 8; i++)
        {
            std::cin >> points[i].x >> points[i].y;
        }

        return new Octagon(points);
    }

    default:
        std::cout << "Invalid option" << std::endl;
        break;
    }
    return nullptr;
}

int main()
{
    int arraySize;
    int figuresCount = 0;
    int choise = 0;
    std::cout << "Firstly, you need to enter array size (you can resize it lately): ";
    std::cin >> arraySize;

    Figure **figuresArray = new Figure *[arraySize];

    while (choise != 8)
    {
        showMenu();
        if (!(std::cin >> choise))
        {
            std::cerr << "Invalid input" << std::endl;
            std::cin.clear();
            continue;
        }

        try
        {
            switch (choise)
            {
            case 1:
            {
                if (figuresCount == arraySize)
                {
                    std::cerr << "Array is full. Resize it first" << std::endl;
                    break;
                }
                Figure *figure = addFigure();
                if (figure != nullptr)
                {
                    figuresArray[figuresCount] = figure;
                    figuresCount++;
                }
                break;
            }
            case 2:
            {
                if (figuresCount == 0)
                {
                    std::cout << "There are no figures" << std::endl;
                    break;
                }
                std::cout << "Enter index of figure you want to remove: ";
                int index;
                std::cin >> index;
                if (index < 0 || index >= figuresCount)
                {
                    std::cerr << "Invalid index" << std::endl;
                    break;
                }
                delete figuresArray[index];
                for (int i = index; i < figuresCount - 1; i++)
                {
                    figuresArray[i] = figuresArray[i + 1];
                }
                figuresArray[figuresCount - 1] = nullptr;
                figuresCount--;
                break;
            }
            case 3:
            {
                for (int i = 0; i < figuresCount; i++)
                {
                    figuresArray[i]->printInfo();
                }
                break;
            }
            case 4:
            {
                if (figuresCount == 0)
                {
                    std::cout << "There are no figures" << std::endl;
                    break;
                }
                std::cout << "Enter index of figure you want to get center of: ";
                int index;
                std::cin >> index;
                if (index < 0 || index >= figuresCount)
                {
                    std::cerr << "Invalid index" << std::endl;
                    break;
                }
                std::cout << "Geometrical Center: " << figuresArray[index]->geometricalCenter() << std::endl;
                break;
            }
            case 5:
            {
                if (figuresCount == 0)
                {
                    std::cout << "There are no figures" << std::endl;
                    break;
                }
                std::cout << "Enter index of figure you want to get area of: ";
                int index;
                std::cin >> index;
                if (index < 0 || index >= figuresCount)
                {
                    std::cerr << "Invalid index" << std::endl;
                    break;
                }
                double area = static_cast<double>(*figuresArray[index]);
                std::cout << "Area: " << area << std::endl;
                break;
            }
            case 6:
            {
                if (figuresCount == 0)
                {
                    std::cout << "There are no figures" << std::endl;
                    break;
                }
                double totalArea = 0;
                for (int i = 0; i < figuresCount; i++)
                {
                    totalArea += static_cast<double>(*figuresArray[i]);
                }
                std::cout << "Total area: " << totalArea << std::endl;
                break;
            }
            case 7:
            {
                std::cout << "Enter new array size: ";

                int newSize;
                std::cin >> newSize;
                if (newSize < figuresCount)
                {
                    std::cerr << "New array size is too small" << std::endl;
                    break;
                }
                Figure **newFiguresArray = new Figure *[newSize];
                for (int i = 0; i < figuresCount; i++)
                {
                    newFiguresArray[i] = figuresArray[i];
                }
                delete[] figuresArray;
                figuresArray = newFiguresArray;
                arraySize = newSize;
                break;
            }
            case 8:
            {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default:
            {
                std::cerr << "Invalid option" << std::endl;
                break;
            }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    for (int i = 0; i < figuresCount; i++)
    {
        delete figuresArray[i];
    }
    delete[] figuresArray;

    return 0;
}