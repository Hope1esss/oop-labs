#pragma once
#include <memory_resource>
#include <map>
#include <stdexcept>

class MyMemoryResource : public std::pmr::memory_resource
{
private:
    std::map<void*, size_t> allocatedBlocks;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void *p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override;

public:
    ~MyMemoryResource();
};

class BadAllocationException : public std::bad_alloc
{
    BadAllocationException() : std::bad_alloc() {}
};