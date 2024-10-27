#include <not_implemented.h>

#include "../include/allocator_global_heap.h"

#include <mutex>

void* allocator_global_heap::find_free_block(size_t size)
{
    void* current = heap_start;

    while (current)
    {
        if (is_block_free(current) && get_block_size(current) >= size)
        {
            return current;
        }
        current = get_next_block(current);
    }
    return nullptr;
}

bool allocator_global_heap::is_block_free(void *block) const
{
    return *reinterpret_cast<bool*>(reinterpret_cast<char*>(block) + sizeof(size_t));
}

size_t allocator_global_heap::get_block_size(void *block) const
{
    return *reinterpret_cast<size_t*>(block);
}


void *allocator_global_heap::get_next_block(void *block) const
{
    return *reinterpret_cast<void**>(reinterpret_cast<char*>(block) + sizeof(size_t) + sizeof(bool));
}

void allocator_global_heap::set_block_size(void* block, bool free)
{

}

void allocator_global_heap::set_block_free(void *block, bool free)
{

}


allocator_global_heap::allocator_global_heap(
    logger *logger):_logger(logger)
{
    //throw not_implemented("allocator_global_heap::allocator_global_heap(logger *)", "your code should be here...");
}

allocator_global_heap::~allocator_global_heap()
{
    //throw not_implemented("allocator_global_heap::~allocator_global_heap()", "your code should be here...");
}

allocator_global_heap::allocator_global_heap(
    allocator_global_heap &&other) noexcept : _logger(other._logger)
{
    other._logger = nullptr;
    //throw not_implemented("allocator_global_heap::allocator_global_heap(allocator_global_heap &&) noexcept", "your code should be here...");
}

allocator_global_heap &allocator_global_heap::operator=(
    allocator_global_heap &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    _logger = other._logger;
    other._logger = nullptr;

    //throw not_implemented("allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&) noexcept", "your code should be here...");
}

[[nodiscard]] void *allocator_global_heap::allocate(
    size_t value_size,
    size_t values_count)
{
    std::lock_guard<std::mutex> lock(_mutex);

    size_t total_size = value_size * values_count;

    if (total_size <= 0)
    {
        return nullptr;
    }

    void* block = find_free_block(total_size);

    if (!block)
    {
        return nullptr;
    }

    size_t remaining_size = get_block_size(block) - total_size - METADATA_SIZE;

    if (remaining_size > 0)
    {
        void* next_block = reinterpret_cast<char*>(block) + METADATA_SIZE + total_size;
        set_block_size(next_block, remaining_size);
        set_block_free(next_block, true);
        set_next_block(next_block, get_next_block(block));
        set_block_size(block, total_size);
        set_next_block(block, next_block);
    }


    //throw not_implemented("[[nodiscard]] void *allocator_global_heap::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_global_heap::deallocate(
    void *at)
{
    throw not_implemented("void allocator_global_heap::deallocate(void *)", "your code should be here...");
}

inline logger *allocator_global_heap::get_logger() const
{
    throw not_implemented("inline logger *allocator_global_heap::get_logger() const", "your code should be here...");
}

inline std::string allocator_global_heap::get_typename() const noexcept
{
    throw not_implemented("inline std::string allocator_global_heap::get_typename() const noexcept", "your code should be here...");
}


