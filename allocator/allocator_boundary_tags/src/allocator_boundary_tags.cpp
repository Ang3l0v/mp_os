#include <not_implemented.h>

#include "../include/allocator_boundary_tags.h"
#include <vector>

void allocator_boundary_tags::coalesce(void* block)
{
    void* next = get_next_block(block);
    if (next < static_cast<char*>(_trusted_memory) + get_total_size() && is_block_free(next)) {
        size_t new_size = get_block_size(block) + get_block_size(next);
        set_block_size(block, new_size);
        set_boundary_tag(block, new_size);
    }


    void* prev = get_previous_block(block);
    if (prev >= _trusted_memory && is_block_free(prev)) {
        size_t new_size = get_block_size(prev) + get_block_size(block);
        set_block_size(prev, new_size);
        set_boundary_tag(prev, new_size);
    }
}

void allocator_boundary_tags::split_block(void* block, size_t requested_size)
{
    size_t remaining_size = get_block_size(block) - requested_size;

    if (remaining_size > sizeof(size_t) * 2) {
        void* new_block = static_cast<char*>(block) + requested_size;
        set_block_size(new_block, remaining_size);
        set_block_free(new_block, true);
        set_boundary_tag(new_block, remaining_size);

        set_block_size(block, requested_size);
        set_boundary_tag(block, requested_size);
    }

}



allocator_boundary_tags::~allocator_boundary_tags()
{
    if (_trusted_memory)
    {
        ::operator delete(_trusted_memory);
    }
    throw not_implemented("allocator_boundary_tags::~allocator_boundary_tags()", "your code should be here...");
}


/*
allocator_boundary_tags::allocator_boundary_tags(
    allocator_boundary_tags const &other)
{
    throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(allocator_boundary_tags const &)", "your code should be here...");
}

allocator_boundary_tags &allocator_boundary_tags::operator=(
    allocator_boundary_tags const &other)
{
    throw not_implemented("allocator_boundary_tags &allocator_boundary_tags::operator=(allocator_boundary_tags const &)", "your code should be here...");
}
*/



allocator_boundary_tags::allocator_boundary_tags(
    allocator_boundary_tags &&other) noexcept
    :_trusted_memory(other._trusted_memory)
{
    other._trusted_memory = nullptr;

    throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(allocator_boundary_tags &&) noexcept", "your code should be here...");
}



/*
allocator_boundary_tags &allocator_boundary_tags::operator=(
    allocator_boundary_tags &&other) noexcept
{
    throw not_implemented("allocator_boundary_tags &allocator_boundary_tags::operator=(allocator_boundary_tags &&) noexcept", "your code should be here...");
}
*/



allocator_boundary_tags::allocator_boundary_tags(
    size_t space_size,
    allocator *parent_allocator,
    logger *logger,
    allocator_with_fit_mode::fit_mode allocate_fit_mode)
{


















    throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(size_t, allocator *, logger *, allocator_with_fit_mode::fit_mode)", "your code should be here...");
}



[[nodiscard]] void *allocator_boundary_tags::allocate(
    size_t value_size,
    size_t values_count)
{















    throw not_implemented("[[nodiscard]] void *allocator_boundary_tags::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_boundary_tags::deallocate(
    void *at)
{

    if (!at) return;

    void* block = static_cast<char*>(at) - sizeof(size_t);
    set_block_free(block, true);
    coalesce(block);

    throw not_implemented("void allocator_boundary_tags::deallocate(void *)", "your code should be here...");
}

inline void allocator_boundary_tags::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{

    throw not_implemented("inline void allocator_boundary_tags::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

inline allocator *allocator_boundary_tags::get_allocator() const
{


    throw not_implemented("inline allocator *allocator_boundary_tags::get_allocator() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept
{
    std::vector<block_info> blocks;
    void* current = _trusted_memory;

    while (current < static_cast<char*>(_trusted_memory) + get_total_size()) {
        blocks.push_back({ current, is_block_free(current), get_block_size(current) });
        current = get_next_block(current);
    }

    return blocks;
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_boundary_tags::get_logger() const
{
    //return logger сделать логгер
    throw not_implemented("inline logger *allocator_boundary_tags::get_logger() const", "your code should be here...");
}

inline std::string allocator_boundary_tags::get_typename() const noexcept
{
    return "allocator_boundary_tags";
    throw not_implemented("inline std::string allocator_boundary_tags::get_typename() const noexcept", "your code should be here...");
}