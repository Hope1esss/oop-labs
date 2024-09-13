#include "../include/checkBracketSequence.h"
bool checkBracketSequence(std::string input_string) {
   int balance = 0;

   if (input_string.empty()) {
      return true;
   }

   if (input_string.length() > 100) {
      throw InvalidStringLengthException();
   }

   for (char ch : input_string) {
      if (ch == '(') {
         balance++;
      } else if (ch == ')') {
         balance--;
      } else {
         throw InvalidCharException();
      }

      if (balance < 0) {
         return false;
      }
   }

   return balance == 0;
}