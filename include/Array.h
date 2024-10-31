#pragma once
#include <memory>
#include <stdexcept>
template <typename T>
class Array
{
public:
    Array();
    Array(const Array &other);
    Array(Array &&other) noexcept;
    ~Array() = default;

    void append(std::shared_ptr<T> item);
    void remove(size_t index);
    size_t getSize() const;
    size_t getCapacity() const;
    double calculateTotalArea() const;
    Array &operator=(const Array &other);
    Array &operator=(Array &&other) noexcept;

    std::shared_ptr<T> &operator[](size_t index);

private:
    size_t size;
    size_t capacity;
    std::unique_ptr<std::shared_ptr<T>[]> data;

    void resize(size_t newCapacity);
};


class OutOfRangeException : public std::out_of_range
{
    public : 
    OutOfRangeException() : std::out_of_range("Index out of range") {}
};

