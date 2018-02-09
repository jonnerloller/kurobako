#include "arrayheap.h"
#include "memorymanager.h"
#include "memorystack.h"
#include "./glm/glm.hpp"
namespace kurobako::memory
{
    uint64 GetSmallestPowerOf2GreaterThanSize(uint64 size)
    {
        f32 num_log = std::log2(static_cast<f32>(size));
        uint64 actual_power = static_cast<uint64>(ceil(num_log));
        return static_cast<uint64>(std::pow(2,actual_power));
    }

    uint64 ArrayHeap::GetBlockIndex(uint64 size,uint32 power_of_heap)
    {
        uint64 power_of_block = static_cast<uint64>(std::log2(size));
        uint64 index = power_of_heap >= power_of_block ? power_of_heap - power_of_block : power_of_heap;
        index = std::min(index, max_node_depth);
        return index;
    }

    uint64 ArrayHeap::GetSizeToReserveForBlockHeaders(uint64 size)
    {
        uint64 maxDepth = GetMaximumDepth(size);
        uint64 sizeOfSmallestBlock = GetSizeOfSmallestPossibleBlock(size, maxDepth);
        uint64 numberOfBlocksToAllocate = GetNumberOfBlockHeadersToAllocate(size, sizeOfSmallestBlock);
        return numberOfBlocksToAllocate * AlignSizeTo16(sizeof(HeapHeader));
    }

    uint64 ArrayHeap::GetTotalSizeToAllocate(uint64 size)
    {
        uint64 sizeToAllocateForHeap = GetSmallestPowerOf2GreaterThanSize(size);
        uint64 sizeToAllocateForHeaders = GetSizeToReserveForBlockHeaders(size);

        return sizeToAllocateForHeap + sizeToAllocateForHeaders;
    }

    uint64 ArrayHeap::GetNumberOfBlockHeadersToAllocate(uint64 size, uint64 sizeOfSmallestPossibleBlock)
    {
        // These should both be powers of 2.
        return size / sizeOfSmallestPossibleBlock;
    }

    uint64 ArrayHeap::GetSizeOfSmallestPossibleBlock(uint64 size, uint64 maxDepth)
    {
        uint64 smallest_block_size = size / static_cast<uint64>(pow(2, maxDepth));
        return std::max(smallest_possible_block_size,smallest_block_size);
    }

    uint64 ArrayHeap::GetMaximumDepth(uint64 size)
    {
        uint64 depth = static_cast<uint64>(std::log2(size));
        depth = std::min(depth, ArrayHeap::max_node_depth);
        return depth;
    }
    struct dummy
    {
        static constexpr uint64 size = 1024 / sizeof(uint64);
        uint64 stuff[size];
        dummy(uint64 j)
        {
            for (int i = 0; i < size; ++i)
            {
                stuff[i] = i + j*size;
            }
        }
        void check(uint64 j)
        {
            for (int i = 0; i < size; ++i)
            {
                assert(stuff[i] == i + j*size);
            }
        }
    };
    dummy* Stuff[1024 * 1024];
    ArrayHeap::ArrayHeap(MemoryStack& allocator, uint64 size)
        :m_allocator(allocator), 
        m_heap_size(AlignSizeTo16(GetSmallestPowerOf2GreaterThanSize(size))),
        m_power_of_heap(static_cast<uint32>(std::log2(m_heap_size))),
        m_actual_size(GetTotalSizeToAllocate(m_heap_size)),
        m_base(reinterpret_cast<uintptr>(allocator.Allocate(m_actual_size))),
        m_destroyed(false)
    {
        HeapHeader* object = reinterpret_cast<HeapHeader*>(m_base);
        object = new(object)HeapHeader{ m_actual_size,0 };
        for (auto &i : m_free_list)
        {
            i = nullptr;
        }
        m_free_list[0] = object;
        
        for (uint64 i = 0; i < 1024*1024; ++i)
        {
            dummy* ptr = (dummy*)Allocate(sizeof(dummy));
            ptr = new(ptr)dummy(i);
            Stuff[i] = ptr;
        }

        for (uint64 i = 0; i < 1024 * 1024; ++i)
        {
            Stuff[i]->check(i);
        }

        for (uint64 i = 0; i < 1024 * 1024; ++i)
        {
            Deallocate(Stuff[i]);
        }
        
    }

    ArrayHeap::~ArrayHeap()
    {
        Destroy();
    }

    void ArrayHeap::Split(HeapHeader& block_header)
    {        
        uint64 new_block_size = block_header.size / 2;
        uintptr sibling_block_header_location = reinterpret_cast<uintptr>(&block_header) + new_block_size;
        assert(sibling_block_header_location < m_base + m_actual_size);
        assert(sibling_block_header_location >= m_base);
        HeapHeader* sibling_block_header = reinterpret_cast<HeapHeader*>(sibling_block_header_location);
        sibling_block_header->item_in_free_list = 0;
        sibling_block_header->size = new_block_size;
        block_header.item_in_free_list = 0;
        block_header.size = new_block_size;        
        InsertBlockIntoFreeList(block_header);
        InsertBlockIntoFreeList(*sibling_block_header);
    }

    void ArrayHeap::InsertBlockIntoFreeList(HeapHeader& block_header)
    {
        uint64 free_list_index = GetBlockIndex(block_header.size, m_power_of_heap);
        assert(free_list_index <= max_node_depth);
        block_header.item_in_free_list = reinterpret_cast<uintptr>(m_free_list[free_list_index]);
        m_free_list[free_list_index] = &block_header;
    }

    ArrayHeap::HeapHeader* ArrayHeap::PopHeaderFromFreeList(uint64 free_list_index)
    {
        assert(free_list_index <= max_node_depth);
        ArrayHeap::HeapHeader* header = nullptr;
        if (m_free_list[free_list_index])
        {
            header = m_free_list[free_list_index];
            assert((header->item_in_free_list & 0xF) == 0);
            m_free_list[free_list_index] = reinterpret_cast<ArrayHeap::HeapHeader*>(header->item_in_free_list);
            header->item_in_free_list = 0;
        }
        return header;
    }
    void ArrayHeap::RemoveHeaderFromFreeList(HeapHeader* header)
    {
        uint64 power_of_size_without_headers = static_cast<uint64>(std::floor(std::log2(header->size)));
        uint64 sizeWithoutHeaders = std::pow(2, power_of_size_without_headers);
        uint64 index_of_free_list = GetBlockIndex(sizeWithoutHeaders,m_power_of_heap);
        
        assert(index_of_free_list <= max_node_depth);

        HeapHeader* prev = nullptr;
        HeapHeader* searchHeader = m_free_list[index_of_free_list];
        while (searchHeader)
        {
            if (searchHeader == header) break;

            prev = searchHeader;
            searchHeader = reinterpret_cast<HeapHeader*>(searchHeader->item_in_free_list);
        }
        
        if (prev)
        {
            prev->item_in_free_list = searchHeader->item_in_free_list;
        }
        else
        {
            m_free_list[index_of_free_list] = reinterpret_cast<HeapHeader*>(searchHeader->item_in_free_list);
        }

    }

    ArrayHeap::HeapHeader* ArrayHeap::GetSmallestBlockToSplit(int64 index)
    {
        int64 searchIndex = index - 1;
        HeapHeader* block_to_split = nullptr;
        while (searchIndex >= 0)
        {
            block_to_split = PopHeaderFromFreeList(searchIndex);
            if (block_to_split)
            {
                return block_to_split;
            }
            searchIndex--;
        }
        return nullptr;
    }
    ArrayHeap::HeapHeader* ArrayHeap::FindBuddy(HeapHeader* header)
    {
        uintptr locationOfCurrentBlock = reinterpret_cast<uintptr>(header);
        uintptr offset = locationOfCurrentBlock - m_base;
        uintptr remainder = offset / header->size;
        uintptr locationOfBuddy = (remainder & 0x1) ? locationOfCurrentBlock - header->size : locationOfCurrentBlock + header->size;
        HeapHeader* buddy = reinterpret_cast<HeapHeader*>(locationOfBuddy);

        return buddy;
    }

    bool ArrayHeap::CanMergeWithBuddy(HeapHeader* left, HeapHeader* right)
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

    ArrayHeap::HeapHeader* ArrayHeap::MergeWithBuddy(HeapHeader* left, HeapHeader* right)
    {
        left->size = left->size * 2;
        RemoveHeaderFromFreeList(right);
        InsertBlockIntoFreeList(*left);
        return nullptr;
    }

    void* ArrayHeap::Allocate(uint64 size)
    {
        uint64 ActualAllocationSize = AlignSizeTo16(GetSmallestPowerOf2GreaterThanSize(size));
        uint64 index = GetBlockIndex(size,m_power_of_heap);
        assert(index <= max_node_depth);

        bool blockFound = false;
        while (blockFound == false)
        {
            if (m_free_list[index])
            {
                HeapHeader* header = PopHeaderFromFreeList(index);
                header->item_in_free_list = 0x1;
                uintptr addressOfActualHeapData = reinterpret_cast<uintptr>(header) + AlignSizeTo16(sizeof(HeapHeader));
                void* ptr = reinterpret_cast<void*>(addressOfActualHeapData);
                return ptr;
            }
            else
            {
                // Out of memory. will probably handle this nicely =.=
                assert(index != 0);
                HeapHeader* header = GetSmallestBlockToSplit(index);
                // Also out of memory.
                assert(header);
                Split(*header);
            }
        }

        return nullptr;
    }

    void ArrayHeap::Deallocate(void* ptr)
    {
        uintptr addressOfObject = reinterpret_cast<uintptr>(ptr);
        assert(addressOfObject > m_base && addressOfObject < m_base + m_actual_size);
        uintptr addressOfBlockHeader = addressOfObject - AlignSizeTo16(sizeof(HeapHeader));
        HeapHeader* header = reinterpret_cast<HeapHeader*>(addressOfBlockHeader);
        uint64 sizeOfObject = header->size - AlignSizeTo16(sizeof(HeapHeader));
        
        uint8* dataWalker = reinterpret_cast<uint8*>(addressOfObject);
        header->item_in_free_list = header->item_in_free_list & ~0x1;
        for (uint64 i = 0; i < sizeOfObject; ++i)
        {
            dataWalker[i] = 0xFA;
        }
        HeapHeader* buddy = FindBuddy(header);
        if (CanMergeWithBuddy(header, buddy))
        {
            MergeWithBuddy(header, buddy);
        }
        else
        {
            InsertBlockIntoFreeList(*header);
        }

    }

    void ArrayHeap::Initialize()
    {

    }

    void ArrayHeap::Destroy()
    {
        if (m_destroyed == false)
        {
            uintptr temp = m_base;
            m_allocator.Deallocate(reinterpret_cast<void*>(temp), m_actual_size);
        }
    }

}
