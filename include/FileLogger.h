#include "Observer.h"
#include <iostream>
#include <fstream>

class FileLogger : public Observer
{
private:
    std::ofstream outputFile;

public:
    explicit FileLogger(const std::string &filename) : outputFile(filename, std::ios::app) {}

    ~FileLogger()
    {
        if (outputFile.is_open())
        {
            outputFile.close();
        }
    }

    void onEvent(const std::string &event) override
    {
        if (outputFile.is_open())
        {
            outputFile << "Event: " << event << std::endl;
        }
    }
};