#include "../include/Array.h"
#include <memory>

template <typename T>
Array<T>::Array() : size(0), capacity(10), data(std::make_unique<std::shared_ptr<T>[]>(capacity)) {}

template <typename T>
Array<T>::Array(const Array &other) : size(other.size), capacity(other.capacity), data(std::make_unique<std::shared_ptr<T>[]>(other.capacity))
{
    for (size_t i = 0; i < other.size_; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
Array<T>::Array(Array &&other) noexcept : size(other.size), capacity(other.capacity), data(std::move(other.data))
{
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
void Array<T>::append(std::shared_ptr<T> item)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }

    data[size++] = std::move(item);
}

template <typename T>
void Array<T>::remove(size_t index)
{
    if (index >= size)
    {
        throw OutOfRangeException();
    }
    for (size_t i = index; i < size - 1; i++)
    {
        data[i] = std::move(data[i + 1]);
    }
    size--;
}

template <typename T>
size_t Array<T>::getSize() const
{
    return size;
}

template <typename T>
size_t Array<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
    if (this == &other)
        return *this;

    size = other.size;
    capacity = other.capacity;
    data = std::make_unique<std::shared_ptr<T>[]>(other.capacity);

    for (size_t i = 0; i < other.size_; i++)
    {
        data[i] = other.data[i];
    }

    return *this;
}

template <typename T>
Array<T> &Array<T>::operator=(Array &&other) noexcept
{
    if (this == &other)
        return *this;

    size = other.size;
    capacity = other.capacity;

    data = std::move(other.data);

    other.size = 0;
    other.capacity = 0;

    return *this;
}

template <typename T>
std::shared_ptr<T> &Array<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw OutOfRangeException();
    }
    return data[index];
}

template <typename T>
void Array<T>::resize(size_t newCapacity)
{
    std::unique_ptr<std::shared_ptr<T>[]> tempData = std::make_unique<std::shared_ptr<T>[]>(newCapacity);
    for (size_t i = 0; i < size; i++)
    {
        tempData[i] = std::move(data[i]);
    }
    capacity = newCapacity;
    data = std::move(tempData);
    delete[] tempData;
}
