#include <iostream>
#include "./include/Eleven.h"

void showMenu()
{
    std::cout << "Choose one of the following:" << std::endl;
    std::cout << "1. Enter two 11-based numbers" << std::endl;
    std::cout << "2. Add up the numbers" << std::endl;
    std::cout << "3. Subtract the second number from the first" << std::endl;
    std::cout << "4. Compare numbers" << std::endl;
    std::cout << "5. Print numbers" << std::endl;
    std::cout << "6. Exit" << std::endl;
}
int main()
{
    std::cout << "Welcome to Eleven Program" << std::endl;
    Eleven num1, num2;
    bool numbersEntered = false;
    int choise = 0;

    while (choise != 6)
    {
        showMenu();
        if (!(std::cin >> choise))
        {
            std::cerr << "Invalid input. Enter number from 1 to 7" << std::endl;
            std::cin.clear();
            continue;
        }

        try
        {
            switch (choise)
            {
            case 1:
            {
                if (numbersEntered)
                {
                    std::cout << "Numbers already entered" << std::endl;
                    break;
                }
                std::string inputNum1, inputNum2;
                std::cout << "Enter first number: ";
                std::cin >> inputNum1;
                num1 = Eleven(inputNum1);
                std::cout << "Enter second number: ";
                std::cin >> inputNum2;
                num2 = Eleven(inputNum2);
                numbersEntered = true;
                std::cout << "Numbers entered" << std::endl;
                break;
            }
            case 2:
            {
                if (!numbersEntered)
                {
                    std::cout << "Please enter numbers before this operation" << std::endl;
                    break;
                }
                Eleven sumResult = num1;
                sumResult += num2;
                std::cout << "Sum of numbers: ";
                for (size_t i = 0; i < sumResult.getSize(); i++)
                {
                    std::cout << sumResult.getData()[i];
                }
                std::cout << std::endl;
                break;
            }
            case 3:
            {
                if (!numbersEntered)
                {
                    std::cout << "Please enter numbers before this operation" << std::endl;
                    break;
                }
                Eleven subResult = num1;
                subResult -= num2;
                std::cout << "Subtraction result: ";
                for (size_t i = 0; i < subResult.getSize(); i++)
                {
                    std::cout << subResult.getData()[i];
                }
                std::cout << std::endl;
                break;
            }
            case 4:
            {
                if (!numbersEntered)
                {
                    std::cout << "Please enter numbers before this operation" << std::endl;
                    break;
                }
                std::cout << "Comparision result: ";
                if (num1 == num2)
                {
                    std::cout << "Equal" << std::endl;
                }
                else if (num1 < num2)
                {
                    std::cout << "First is less than second" << std::endl;
                }
                else if (num1 > num2)
                {
                    std::cout << "First is greater than second" << std::endl;
                }
                break;
            }

            case 5:
            {
                if (!numbersEntered)
                {
                    std::cout << "Please enter numbers before this operation" << std::endl;
                    break;
                }
                std::cout << "First number: ";
                for (size_t i = 0; i < num1.getSize(); i++)
                {
                    std::cout << num1.getData()[i];
                }
                std::cout << std::endl;

                std::cout << "Second number: ";
                for (size_t i = 0; i < num2.getSize(); i++)
                {
                    std::cout << num2.getData()[i];
                }
                std::cout << std::endl;
                break;
            }
            case 6:
            {
                std::cout << "Bye!" << std::endl;
                delete &num1;
                delete &num2;
                break;
            }

            default:
                std::cout << "Invalid option" << std::endl;
                break;
            }
        }
        catch (const InvalidDigit &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const NegativeSubtraction &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}