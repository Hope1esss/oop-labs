#pragma once
#include <initializer_list>
#include <stdexcept>

void validateDigit(unsigned char digit);

class Eleven {
  public:
   Eleven();
   Eleven(const size_t &length, unsigned char value = 0);
   Eleven(const std::initializer_list<unsigned char> &valuesList);
   Eleven(const std::string &value);
   Eleven(const Eleven &other);
   Eleven(Eleven &&other) noexcept;
   virtual ~Eleven() noexcept;

   Eleven &operator=(const Eleven &other);
   Eleven &operator+=(const Eleven &other);
   Eleven &operator-=(const Eleven &other);

   bool operator==(const Eleven &other) const;
   bool operator<(const Eleven &other) const;
   bool operator>(const Eleven &other) const;

   size_t getSize() const;
   unsigned char *getData() const;

  private:
   size_t size_;
   unsigned char *data_;
};

class InvalidDigit : public std::invalid_argument {
  public:
   InvalidDigit()
       : std::invalid_argument("Invalid digit: It must be between 0 and 10(A)") {}
};

class NegativeSubtraction : public std::invalid_argument {
  public:
   NegativeSubtraction()
       : std::invalid_argument("Negative substraction: Result is negative") {}
};
