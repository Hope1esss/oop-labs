#pragma once
#include <memory_resource>
#include <map>
#include <stdexcept>

class MyMemoryResource : public std::pmr::memory_resource
{
public:
    MyMemoryResource(size_t poolSize);
    ~MyMemoryResource();

protected:
    void *do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override;

private:
    std::map<void *, size_t> allocatedBlocks;
    void *pool;
    size_t poolSize;
};

class DeallocateError : public std::invalid_argument
{
public:
    DeallocateError() : std::invalid_argument("Unknown address to deallocate") {}
};