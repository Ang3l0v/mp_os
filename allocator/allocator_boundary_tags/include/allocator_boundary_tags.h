#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H

#include <allocator_guardant.h>
#include <allocator_test_utils.h>
#include <allocator_with_fit_mode.h>
#include <logger_guardant.h>
#include <typename_holder.h>
#include <mutex>
class allocator_boundary_tags final:
    private allocator_guardant,
    public allocator_test_utils,
    public allocator_with_fit_mode,
    private logger_guardant,
    private typename_holder
{

private:
    
    void *_trusted_memory;

public:
    
    ~allocator_boundary_tags() override;
    
    allocator_boundary_tags(
        allocator_boundary_tags const &other) = delete;
    
    allocator_boundary_tags &operator=(
        allocator_boundary_tags const &other) = delete;
    
    allocator_boundary_tags(
        allocator_boundary_tags &&other) noexcept;
    
    allocator_boundary_tags &operator=(
        allocator_boundary_tags &&other) noexcept = delete;

public:
    
    explicit allocator_boundary_tags(
        size_t space_size,
        allocator *parent_allocator = nullptr,
        logger *logger = nullptr,
        allocator_with_fit_mode::fit_mode allocate_fit_mode = allocator_with_fit_mode::fit_mode::first_fit);

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

public:
    
    inline void set_fit_mode(
        allocator_with_fit_mode::fit_mode mode) override;

private:
    
    //inline allocator *get_allocator() const override;

public:
    
    std::vector<allocator_test_utils::block_info> get_blocks_info() const noexcept override;

private:
    
    //inline logger *get_logger() const override;

private:
    
    inline std::string get_typename() const noexcept override;

public:


private:

    void* get_next_block(void* block) const
    {
        return static_cast<char*>(block) + get_block_size(block);
    }

    void set_block_free(void* block, bool is_free)
    {
        *reinterpret_cast<bool*>(static_cast<char*>(block) + sizeof(size_t)) = is_free;
    }

    bool is_block_free(void* block)
    {
        return *reinterpret_cast<bool*>(static_cast<char*>(block) + sizeof(size_t));
    }

    void set_block_size(void* block, size_t size)
    {
        *reinterpret_cast<size_t*>(block) = size;
    }

    void set_total_size(size_t size) const
    {
        *reinterpret_cast<size_t*>(_trusted_memory) = size;
    }

    void set_parent_allocator(allocator* parent)
    {
        *reinterpret_cast<allocator**>(static_cast<char*>(_trusted_memory) + sizeof(size_t)) = parent;
    }

    void set_logger(logger* log)
    {
        *reinterpret_cast<logger**>(static_cast<char*>(_trusted_memory) + sizeof(size_t) * 2) = log;
    }

    void set_mutex()
    {
        new (static_cast<char*>(_trusted_memory) + sizeof(size_t) * 3) std::mutex();
    }

    size_t get_block_size(void* block) const
    {
        return *reinterpret_cast<size_t*>(block);
    }

    size_t get_total_size() const
    {
        return *reinterpret_cast<const size_t*>(_trusted_memory);
    }

    void* get_parent_allocator() const
    {
        return *reinterpret_cast<allocator**>(static_cast<char*>(_trusted_memory) + sizeof(size_t));
    }

    void* get_logger()
    {
        return *reinterpret_cast<logger**>(static_cast<char*>(_trusted_memory) + sizeof(size_t) * 2);
    }

    std::mutex& get_mutex() const
    {
        return *reinterpret_cast<std::mutex*>(static_cast<char*>(_trusted_memory) + sizeof(size_t) * 3);
    }

    void* get_fit_mode_adress() const
    {
        return static_cast<char*>(_trusted_memory) + sizeof(size_t) * 4;
    }



};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H