#include "Observer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
            outputFile << event << std::endl;
        }
    }

    void getLogs(std::vector<std::string> &lines, std::string &filename)
    {
        std::ifstream inputFile(filename);
        std::string line;
        while (std::getline(inputFile, line))
        {
            lines.push_back(line);
        }
        inputFile.close();
    }
};