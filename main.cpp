#include <iostream>
#include <string>
#include "checkBracketSequence.h"
int main() {
   std::string input_string;
   std::cout << "Enter your bracket sequence: ";
   std::cin >> input_string;

   bool result;

   try {
      result = checkBracketSequence(input_string);
      std::cout << "result: " << (result ? "true" : "false") << std::endl;
   } catch (const InvalidStringLengthException& e) {
      std::cerr << e.what() << std::endl;
   } catch (const InvalidCharException& e) {
      std::cerr << e.what() << std::endl;
   }

   return 0;
}