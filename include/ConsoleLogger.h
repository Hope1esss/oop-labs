#include "Observer.h"
#include <iostream>

class ConsoleLogger : public Observer
{
public:
    void onEvent(const std::string &event) override
    {
        std::cout << "Event: " << event << std::endl;
    }
};