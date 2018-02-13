#ifndef MEMORYBLOCKHEAP
#define MEMORYBLOCKHEAP
#include "types/sizedtypes.h"
#include <array>
namespace kurobako::memory
{
    class stack;

    class block_heap
    {
    public:
        block_heap(memory::stack& allocator, uint64 size);
        ~block_heap();

        void* allocate(uint64 size);
        void  deallocate(void* ptr);
        
        static constexpr uint64 max_node_depth = 20;
        static constexpr uint64 smallest_possible_block_size = 512;
    private:


        struct block_header
        {
            uint64  size = 0;
            uintptr item_in_free_list = 0;
        };

        void split(block_heap::block_header* block_header);
        block_header* get_smallest_block_to_split(int64 index);
        void destroy_heap();
        
        
        static uint64 get_size_to_reserve_for_block_header(uint64 size);
        static uint64 get_total_size_to_allocate(uint64 size);
        static uint64 get_number_of_blocks_to_allocate(uint64 size, uint64 size_of_smallest_possible_block);
        static uint64 get_size_of_smallest_possible_block(uint64 size, uint64 max_depth);
        static uint64 get_max_depth(uint64 size);
        static uint64 get_block_index(uint64 size,uint32 power_of_heap);

        block_header* find_buddy_block(block_header* header);
        static bool can_merge_with_buddy(block_header* left, block_header* right);
        block_header* merge_with_buddy(block_header* left, block_header* right);

        
        
        // free_list functions. maybe could have used a generic linked list.
        void insert_block_into_free_list(block_header* header);
        block_header* pop_header_from_free_list(uint64 freelistIndex);
        void remove_header_from_free_list(block_header* header);
        
        bool m_destroyed;
        uint64 m_heap_size;
        uint64 m_actual_size;
        uint32 m_power_of_heap;
        uintptr m_base;
        memory::stack& m_allocator;
        std::array<block_header*, max_node_depth + 1> m_free_list;

        friend class memory_manager;
    };
}

#endif