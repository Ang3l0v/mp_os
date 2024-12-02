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

    fit_mode get_fit_mode() const
    {
        return *reinterpret_cast<const fit_mode*>(static_cast<const char*>(_trusted_memory) + sizeof(size_t) * 4);
    }

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
        set_footer_size(block, size);
    }

    void set_footer_size(void* block, size_t size)
    {
        void* footer = static_cast<char*>(block) + size - sizeof(size_t);
        *reinterpret_cast<size_t*>(footer) = size;
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

    void* get_data_start() const
    {
        return static_cast<char*>(_trusted_memory) + sizeof(size_t) * 5;
    }

    void* get_memory_end()
    {
        return static_cast<char*>(_trusted_memory) + get_total_size();
    }

    void* get_fit_mode_adress() const
    {
        return static_cast<char*>(_trusted_memory) + sizeof(size_t) * 4;
    }

    void* get_prev_block(void* block)
    {
        size_t prev_size = *reinterpret_cast<size_t*>(static_cast<char*>(block) - sizeof (size_t));
        return static_cast<char*>(block) - prev_size;
    }


    void split_block(void* block, size_t requested_size)
    {
        size_t block_size = get_block_size(block);

        if (block_size >= requested_size + sizeof(size_t) * 3)
        {
            void* next_block =  static_cast<char*>(block) + requested_size;

            size_t remaining_size = block_size - requested_size;

            set_block_size(next_block, requested_size);
            set_block_free(block, true);

            set_block_size(block, remaining_size);
            set_block_free(block, false);
        }
    }

    void coalesce(void* block)
    {
        size_t block_size = get_block_size(block);
        if (has_prev_block(block))
        {
            void* previous_block = get_prev_block(block);
            if (is_block_free(previous_block))
            {
                size_t previous_block_size = get_block_size(previous_block);
                block_size += previous_block_size;
                set_block_size(previous_block, block_size); // Обновляем размер объединённого блока
                block = previous_block; // Смещаем текущий блок
            }
        }

        if (has_next_block(block))
        {
            void* next_block = get_next_block(block);
            if (is_block_free(next_block))
            {
                size_t next_block_size = get_block_size(next_block);
                block_size += next_block_size;
                set_block_size(block, block_size); // Обновляем размер объединённого блока
            }
        }
    }


    bool has_next_block(void* block)
    {
        return get_next_block(block) < get_memory_end();
    }

    bool has_prev_block(void* block)
    {
        return block > get_data_start();
    }
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H