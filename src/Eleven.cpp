#include "../include/Eleven.h"
#include <iostream>

void validateDigit(unsigned char digit)
{
   if ((digit >= '0' && digit <= '9') || digit == 'A' || digit == 'a')
   {
      return;
   }
   else
   {
      throw InvalidDigit();
   }
}

int elevenToDecimal(unsigned char digit)
{
   if (digit >= '0' && digit <= '9')
   {
      return digit - '0';
   }
   return digit - 'A' + 10;
}

unsigned char decimalToEleven(int digit)
{
   if (digit >= 0 && digit <= 9)
   {
      return digit + '0';
   }
   return digit - 10 + 'A';
}
Eleven::Eleven() : size_(0), data_(nullptr) {}

Eleven::Eleven(const size_t &length, unsigned char value)
{
   validateDigit(value);
   size_ = length;
   data_ = new unsigned char[length];
   for (int i = 0; i < length; i++)
   {
      data_[i] = value;
   }
}

Eleven::Eleven(const std::initializer_list<unsigned char> &valuesList)
{
   size_ = valuesList.size();
   data_ = new unsigned char[size_];

   size_t i = 0;

   for (unsigned char digit : valuesList)
   {
      validateDigit(digit);
      data_[i++] = digit;
   }
}

Eleven::Eleven(const std::string &value)
{
   size_ = value.size();
   data_ = new unsigned char[size_];

   for (size_t i = 0; i < size_; i++)
   {
      validateDigit(value[i]);
      data_[i] = value[i];
   }
}

Eleven::Eleven(const Eleven &other)
{

   size_ = other.size_;
   data_ = new unsigned char[size_];
   for (size_t i = 0; i < size_; i++)
   {
      data_[i] = other.data_[i];
   }
}

Eleven::Eleven(Eleven &&other) noexcept
{
   size_ = other.size_;
   data_ = other.data_;
   other.data_ = nullptr;
   other.size_ = 0;
}

Eleven &Eleven::operator=(const Eleven &other)
{
   if (this == &other)
   {
      return *this;
   }

   delete[] data_;
   size_ = other.size_;
   data_ = new unsigned char[size_];
   for (size_t i = 0; i < size_; i++)
   {
      data_[i] = other.data_[i];
   }
   return *this;
}

Eleven &Eleven::operator+=(const Eleven &other)
{
   size_t maxSize = std::max(size_, other.size_);
   unsigned char *result = new unsigned char[maxSize + 1];

   int carry = 0;
   for (size_t i = 0; i < maxSize; i++)
   {
      int digit1 = (i < size_) ? elevenToDecimal(data_[i]) : 0;
      int digit2 = (i < other.size_)
                       ? elevenToDecimal(other.data_[i])
                       : 0;

      int sum = digit1 + digit2 + carry;
      carry = sum / 11;
      result[i] = decimalToEleven(sum % 11);
   }

   if (carry > 0)
   {
      result[maxSize - 1] = decimalToEleven(carry);
      maxSize++;
   }

   delete[] data_;
   data_ = result;
   size_ = maxSize;

   return *this;
}

Eleven &Eleven::operator-=(const Eleven &other)
{
   if (size_ < other.size_)
   {
      throw NegativeSubtraction();
   }

   int borrow = 0;

   for (size_t i = 0; i < size_; i++)
   {
      int currentDigit = elevenToDecimal(data_[i]) - borrow;
      int otherDigit = (i < other.size_)
                           ? elevenToDecimal(other.data_[i])
                           : 0;

      if (currentDigit < otherDigit)
      {
         currentDigit += 11;
         borrow = 1;
      }
      else
      {
         borrow = 0;
      }

      data_[i] = decimalToEleven(currentDigit - otherDigit);
   }

   if (borrow != 0)
   {
      throw NegativeSubtraction();
   }

   size_t newSize = size_;
   while (newSize > 1 && data_[newSize - 1] == '0')
   {
      newSize--;
   }

   if (newSize != size_)
   {
      unsigned char *newData = new unsigned char[newSize];
      for (size_t i = 0; i < newSize; i++)
      {
         newData[i] = data_[i];
      }
      delete[] data_;
      data_ = newData;
      size_ = newSize;
   }

   return *this;
}

bool Eleven::operator==(const Eleven &other) const
{
   if (size_ != other.size_)
   {
      return false;
   }
   for (int i = 0; i < size_; i++)
   {
      if (data_[i] != other.data_[i])
      {
         return false;
      }
   }
   return true;
}

bool Eleven::operator<(const Eleven &other) const
{
   if (size_ != other.size_)
   {
      return size_ < other.size_;
   }

   for (size_t i = 0; i < size_; i++)
   {
      int digit1 = elevenToDecimal(data_[size_ - i]);
      int digit2 = elevenToDecimal(other.data_[size_ - i]);

      if (digit1 != digit2)
      {
         return digit1 < digit2;
      }
   }

   return false;
}

bool Eleven::operator>(const Eleven &other) const
{
   if (size_ != other.size_)
   {
      return size_ > other.size_;
   }

   for (size_t i = 0; i < size_; i++)
   {
      int digit1 = elevenToDecimal(data_[size_ - i]);
      int digit2 = elevenToDecimal(other.data_[size_ - i]);

      if (digit1 != digit2)
      {
         return digit1 > digit2;
      }
   }

   return false;
}

size_t Eleven::getSize() const { return size_; }

unsigned char *Eleven::getData() const { return data_; }

Eleven::~Eleven() noexcept
{
   delete[] data_;
   data_ = nullptr;
   size_ = 0;
}
