#include "../include/MyMemoryResource.h"

MyMemoryResource::MyMemoryResource(size_t size) : poolSize(size)
{
    pool = ::operator new(poolSize);
}

MyMemoryResource::~MyMemoryResource()
{
    ::operator delete(pool);
}

void *MyMemoryResource::do_allocate(size_t bytes, size_t alignment)
{
    void *ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocatedBlocks[ptr] = bytes;
    return ptr;
}

void MyMemoryResource::do_deallocate(void *ptr, size_t bytes, size_t alignment)
{
    if (allocatedBlocks.erase(ptr) > 0)
    {
        ::operator delete(ptr, std::align_val_t(alignof(std::max_align_t)));
    }
    else
    {
        throw DeallocateError();
    }
}

bool MyMemoryResource::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    return this == &other;
}