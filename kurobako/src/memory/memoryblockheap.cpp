#include "memoryblockheap.h"
#include "memorymanager.h"
#include "memorystack.h"
#include "./glm/glm.hpp"
namespace kurobako::memory
{
    uint64 smallest_power_of_2_greater_than_num(uint64 num)
    {
        f32 num_log = std::log2(static_cast<f32>(num));
        uint64 actual_power = static_cast<uint64>(ceil(num_log));
        return static_cast<uint64>(std::pow(2,actual_power));
    }

    uint64 block_heap::get_block_index(uint64 size,uint32 power_of_heap)
    {
        uint64 power_of_block = static_cast<uint64>(std::log2(size));
        uint64 index = power_of_heap >= power_of_block ? power_of_heap - power_of_block : power_of_heap;
        index = std::min(index, max_node_depth);
        return index;
    }

    uint64 block_heap::get_size_to_reserve_for_block_header(uint64 size)
    {
        uint64 maxDepth = get_max_depth(size);
        uint64 size_of_smallest_possible_block = get_size_of_smallest_possible_block(size, maxDepth);
        uint64 number_of_blocks_to_allocate = get_number_of_blocks_to_allocate(size, size_of_smallest_possible_block);
        return number_of_blocks_to_allocate * align_to_16(sizeof(block_header));
    }

    uint64 block_heap::get_total_size_to_allocate(uint64 size)
    {
        uint64 size_to_allocate_for_heap = smallest_power_of_2_greater_than_num(size);
        uint64 size_to_allocate_for_headers = get_size_to_reserve_for_block_header(size);

        return size_to_allocate_for_heap + size_to_allocate_for_headers;
    }

    uint64 block_heap::get_number_of_blocks_to_allocate(uint64 size, uint64 size_of_smallest_possible_block)
    {
        // These should both be powers of 2.
        return size / size_of_smallest_possible_block;
    }

    uint64 block_heap::get_size_of_smallest_possible_block(uint64 size, uint64 max_depth)
    {
        uint64 smallest_block_size = size / static_cast<uint64>(pow(2, max_depth));
        return std::max(smallest_possible_block_size,smallest_block_size);
    }

    uint64 block_heap::get_max_depth(uint64 size)
    {
        uint64 depth = static_cast<uint64>(std::log2(size));
        depth = std::min(depth, block_heap::max_node_depth);
        return depth;
    }

    block_heap::block_heap(memory::stack& allocator, uint64 size)
        :m_allocator(allocator), 
        m_heap_size(align_to_16(smallest_power_of_2_greater_than_num(size))),
        m_power_of_heap(static_cast<uint32>(std::log2(m_heap_size))),
        m_actual_size(get_total_size_to_allocate(m_heap_size)),
        m_base(reinterpret_cast<uintptr>(allocator.allocate(m_actual_size))),
        m_destroyed(false)
    {
        block_header* object = reinterpret_cast<block_header*>(m_base);
        object = new(object)block_header{ m_actual_size,0 };
        for (auto &i : m_free_list)
        {
            i = nullptr;
        }
        m_free_list[0] = object;
    }

    block_heap::~block_heap()
    {
        destroy_heap();
    }

    void block_heap::split(block_heap::block_header* header)
    {        
        assert(header);

        uint64 new_block_size = header->size / 2;
        uintptr sibling_block_header_location = reinterpret_cast<uintptr>(header) + new_block_size;

        assert(sibling_block_header_location < m_base + m_actual_size);
        assert(sibling_block_header_location >= m_base);

        block_heap::block_header* sibling_block_header = reinterpret_cast<block_heap::block_header*>(sibling_block_header_location);

        sibling_block_header->item_in_free_list = 0;
        sibling_block_header->size = new_block_size;
        header->item_in_free_list = 0;
        header->size = new_block_size;

        insert_block_into_free_list(header);
        insert_block_into_free_list(sibling_block_header);
    }

    void block_heap::insert_block_into_free_list(block_heap::block_header* header)
    {
        assert(header);
        uint64 free_list_index = get_block_index(header->size, m_power_of_heap);
        assert(free_list_index <= max_node_depth);

        header->item_in_free_list = reinterpret_cast<uintptr>(m_free_list[free_list_index]);
        m_free_list[free_list_index] = header;
    }

    block_heap::block_header* block_heap::pop_header_from_free_list(uint64 free_list_index)
    {
        assert(free_list_index <= max_node_depth);
        block_heap::block_header* header = nullptr;
        if (m_free_list[free_list_index])
        {
            header = m_free_list[free_list_index];
            assert((header->item_in_free_list & 0xF) == 0);
            m_free_list[free_list_index] = reinterpret_cast<block_heap::block_header*>(header->item_in_free_list);
            header->item_in_free_list = 0;
        }
        return header;
    }
    void block_heap::remove_header_from_free_list(block_header* header)
    {
        uint64 power_of_size_without_headers = static_cast<uint64>(std::floor(std::log2(header->size)));
        uint64 sizeWithoutHeaders = std::pow(2, power_of_size_without_headers);
        uint64 index_of_free_list = get_block_index(sizeWithoutHeaders,m_power_of_heap);
        
        assert(index_of_free_list <= max_node_depth);

        block_header* prev = nullptr;
        block_header* search_header = m_free_list[index_of_free_list];
        while (search_header)
        {
            if (search_header == header) break;

            prev = search_header;
            search_header = reinterpret_cast<block_header*>(search_header->item_in_free_list);
        }
        
        if (prev)
        {
            prev->item_in_free_list = search_header->item_in_free_list;
        }
        else
        {
            m_free_list[index_of_free_list] = reinterpret_cast<block_header*>(search_header->item_in_free_list);
        }

    }

    block_heap::block_header* block_heap::get_smallest_block_to_split(int64 index)
    {
        int64 searchIndex = index - 1;
        block_header* block_to_split = nullptr;
        while (searchIndex >= 0)
        {
            block_to_split = pop_header_from_free_list(searchIndex);
            if (block_to_split)
            {
                return block_to_split;
            }
            searchIndex--;
        }
        return nullptr;
    }
    block_heap::block_header* block_heap::find_buddy_block(block_header* header)
    {
        uintptr locationOfCurrentBlock = reinterpret_cast<uintptr>(header);
        uintptr offset = locationOfCurrentBlock - m_base;
        uintptr remainder = offset / header->size;
        uintptr locationOfBuddy = (remainder & 0x1) ? locationOfCurrentBlock - header->size : locationOfCurrentBlock + header->size;
        block_header* buddy = reinterpret_cast<block_header*>(locationOfBuddy);

        return buddy;
    }

    bool block_heap::can_merge_with_buddy(block_header* left, block_header* right)
    {
        int8 left_allocation_pattern = left->item_in_free_list & 0xF;
        int8 right_allocation_pattern = right->item_in_free_list & 0xF;
        if (left->size == right->size &&
            left_allocation_pattern == right_allocation_pattern)
        {
            return true;
        }
        return false;
    }

    block_heap::block_header* block_heap::merge_with_buddy(block_header* left, block_header* right)
    {
        left->size = left->size * 2;
        remove_header_from_free_list(right);
        insert_block_into_free_list(left);
        return nullptr;
    }

    void* block_heap::allocate(uint64 size)
    {
        uint64 actual_allocation_size = align_to_16(smallest_power_of_2_greater_than_num(size));
        uint64 index = get_block_index(size,m_power_of_heap);
        assert(index <= max_node_depth);

        bool blockFound = false;
        while (blockFound == false)
        {
            if (m_free_list[index])
            {
                block_header* header = pop_header_from_free_list(index);
                header->item_in_free_list = 0x1;
                uintptr address_of_actual_heap_data = reinterpret_cast<uintptr>(header) + align_to_16(sizeof(block_header));
                void* ptr = reinterpret_cast<void*>(address_of_actual_heap_data);
                return ptr;
            }
            else
            {
                // Out of memory. will probably handle this nicely =.=
                assert(index != 0);
                block_heap::block_header* header = get_smallest_block_to_split(index);
                // Also out of memory.
                assert(header);
                split(header);
            }
        }

        return nullptr;
    }

    void block_heap::deallocate(void* ptr)
    {
        uintptr address_of_object = reinterpret_cast<uintptr>(ptr);
        assert(address_of_object > m_base && address_of_object < m_base + m_actual_size);
        uintptr address_of_block_header = address_of_object - align_to_16(sizeof(block_header));
        block_header* header = reinterpret_cast<block_header*>(address_of_block_header);
        uint64 sizeOfObject = header->size - align_to_16(sizeof(block_header));
        
        uint8* dataWalker = reinterpret_cast<uint8*>(address_of_object);
        header->item_in_free_list = header->item_in_free_list & ~0x1;

        for (uint64 i = 0; i < sizeOfObject; ++i)
        {
            dataWalker[i] = 0xFA;
        }

        block_header* buddy = find_buddy_block(header);
        if (can_merge_with_buddy(header, buddy))
        {
            merge_with_buddy(header, buddy);
        }
        else
        {
            insert_block_into_free_list(header);
        }

    }

    void block_heap::destroy_heap()
    {
        if (m_destroyed == false)
        {
            uintptr temp = m_base;
            m_allocator.deallocate(reinterpret_cast<void*>(temp), m_actual_size);
        }
    }

}
