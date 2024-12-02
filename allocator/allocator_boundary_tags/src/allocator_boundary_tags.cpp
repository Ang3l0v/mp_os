#include <not_implemented.h>

#include "../include/allocator_boundary_tags.h"
#include <vector>
#include <mutex>



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

allocator_boundary_tags &allocator_boundary_tags::operator=(
    allocator_boundary_tags &&other) noexcept
{
    throw not_implemented("allocator_boundary_tags &allocator_boundary_tags::operator=(allocator_boundary_tags &&) noexcept", "your code should be here...");
}

 inline logger *allocator_boundary_tags::get_logger() const
{
    //return logger сделать логгер
    throw not_implemented("inline logger *allocator_boundary_tags::get_logger() const", "your code should be here...");
}

inline allocator *allocator_boundary_tags::get_allocator() const
{
    throw not_implemented("inline allocator *allocator_boundary_tags::get_allocator() const", "your code should be here...");
}

*/

allocator_boundary_tags::allocator_boundary_tags(
        allocator_boundary_tags &&other) noexcept
        :_trusted_memory(other._trusted_memory)
{
    other._trusted_memory = nullptr;
    //throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(allocator_boundary_tags &&) noexcept", "your code should be here...");
}


allocator_boundary_tags::~allocator_boundary_tags()
{
    if (_trusted_memory)
    {
        ::operator delete(_trusted_memory);
    }
    //throw not_implemented("allocator_boundary_tags::~allocator_boundary_tags()", "your code should be here...");
}


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
    std::lock_guard<std::mutex> lock(get_mutex());

    size_t requested_size = value_size * values_count + sizeof(size_t) * 3;

    void* best_block = nullptr;
    size_t best_size = std::numeric_limits<size_t>::max();
    void* worst_block = nullptr;
    size_t worst_size = 0;

    void* current_block = get_data_start();

    while (current_block < get_memory_end())
    {
        size_t current_block_size = get_block_size(current_block);

        if(is_block_free(current_block) && current_block_size >= requested_size)
        {
            switch (get_fit_mode())
            {
                case fit_mode::first_fit:
                    split_block(current_block, requested_size);
                    set_block_free(current_block, false);
                    return static_cast<char*>(current_block) + sizeof(size_t) * 2;
                case fit_mode::the_best_fit:
                    if (current_block_size < best_size)
                    {
                        best_size = current_block_size;
                        best_block = current_block;
                    }
                    break;
                case fit_mode::the_worst_fit:
                    if (current_block_size > worst_size)
                    {
                        worst_size = current_block_size;
                        worst_block = current_block;
                    }
                    break;
            }
        }
        current_block = get_next_block(current_block);
    }

    if (get_fit_mode() == fit_mode::the_best_fit && best_block != nullptr)
    {
        split_block(best_block, requested_size);
        set_block_free(best_block, false);
        return static_cast<char*>(best_block) + sizeof(size_t) * 2;
    }

    if (get_fit_mode() == fit_mode::the_worst_fit && worst_block != nullptr)
    {
        split_block(worst_block, requested_size);
        set_block_free(worst_block, false);
        return static_cast<char*>(worst_block) + sizeof(size_t) * 2;
    }

    return nullptr;
    //throw not_implemented("[[nodiscard]] void *allocator_boundary_tags::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_boundary_tags::deallocate(
    void *at)
{
    throw not_implemented("void allocator_boundary_tags::deallocate(void *)", "your code should be here...");
}

inline void allocator_boundary_tags::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    std::lock_guard<std::mutex> lock(get_mutex());

    *reinterpret_cast<fit_mode*>(get_fit_mode_adress()) = mode;
    //throw not_implemented("inline void allocator_boundary_tags::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}


std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept", "your code should be here...");
}



inline std::string allocator_boundary_tags::get_typename() const noexcept
{
    return "allocator_boundary_tags";
    throw not_implemented("inline std::string allocator_boundary_tags::get_typename() const noexcept", "your code should be here...");
}