#pragma once
#include <stdexcept>
#include <string>

class InvalidStringLengthException : public std::runtime_error {
  public:
   InvalidStringLengthException()
       : std::runtime_error("String length must be between 0 and 100") {}
};

class InvalidCharException : public std::invalid_argument {
  public:
   InvalidCharException()
       : std::invalid_argument("String must contain only brackets") {}
};

bool checkBracketSequence(std::string input_string);
