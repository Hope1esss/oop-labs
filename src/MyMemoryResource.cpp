#include "../include/MyMemoryResource.h"

void *MyMemoryResource::do_allocate(size_t bytes, size_t alignment)
{
    void *p = ::operator new(bytes);
    allocatedBlocks[p] = bytes;
    return p;
}

void MyMemoryResource::do_deallocate(void *p, size_t bytes, size_t alignment)
{
    allocatedBlocks.erase(p);
    ::operator delete(p);
}

bool MyMemoryResource::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    return this == &other;
}

MyMemoryResource::~MyMemoryResource()
{
    for (auto &[ptr, size] : allocatedBlocks)
    {
        ::operator delete(ptr);
    }
}