#include "../include/Eleven.h"
#include <iostream>

void validateDigit(unsigned char digit) {
   if (digit < 0 || (digit > 'A' && digit < 'a') || digit > 'a') {
      throw InvalidDigit();
   }
}

Eleven::Eleven(const size_t &n, unsigned char t) {
   validateDigit(t);
   size_ = n;
   data_ = new unsigned char[n];
   for (int i = 0; i < n; i++) {
      data_[i] = t;
   }
}

Eleven::Eleven(const std::initializer_list<unsigned char> &t) {
   size_ = t.size();
   data_ = new unsigned char[size_];

   size_t i = 0;

   for (unsigned char digit : t) {
      validateDigit(digit);
      data_[i++] = digit;
   }
}

Eleven::Eleven(const std::string &t) {
   size_ = t.size();
   data_ = new unsigned char[size_];

   for (size_t i = 0; i < size_; i++) {
      validateDigit(t[i]);
      data_[i] = t[i];
   }
}

Eleven::Eleven(const Eleven &other) {
   size_ = other.size_;
   data_ = new unsigned char[size_];
   for (size_t i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
   }
}

Eleven::Eleven(Eleven &&other) noexcept {
   size_ = other.size_;
   data_ = other.data_;
   other.data_ = nullptr;
   other.size_ = 0;
}

Eleven &Eleven::operator=(const Eleven &other) {
   if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      data_ = new unsigned char[size_];
      for (size_t i = 0; i < size_; i++) {
         data_[i] = other.data_[i];
      }
   }
   return *this;
}
