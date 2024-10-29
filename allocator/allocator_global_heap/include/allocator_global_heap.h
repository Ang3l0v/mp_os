#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H

#include <allocator.h>
#include <logger.h>
#include <logger_guardant.h>
#include <typename_holder.h>
#include <mutex>
class allocator_global_heap final:
    public allocator,
    private logger_guardant,
    private typename_holder
{

private:
    
    logger *_logger;


public:
    
    explicit allocator_global_heap(
        logger *logger = nullptr);
    
    ~allocator_global_heap() override;
    
    allocator_global_heap(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap &operator=(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap(
        allocator_global_heap &&other) noexcept;
    
    allocator_global_heap &operator=(
        allocator_global_heap &&other) noexcept;

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

public:
    
    void foo()
    {};

private:
    
    inline logger *get_logger() const override;

private:
    
    inline std::string get_typename() const noexcept override;

public:


    bool is_block_free(void* block) const;

    size_t get_block_size(void* block) const;

    void* get_next_block(void* block) const;

    void set_block_free(void* block, bool free);

    void set_block_size(void* block, size_t size);
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H