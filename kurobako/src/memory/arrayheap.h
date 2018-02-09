#ifndef ARRAYHEAP_H
#define ARRAYHEAP_H
#include "types/sizedtypes.h"
#include <array>
namespace kurobako::memory
{
    class MemoryStack;

    class ArrayHeap
    {
    public:
        ArrayHeap(MemoryStack& allocator, uint64 size);
        ~ArrayHeap();

        void* Allocate(uint64 size);
        void  Deallocate(void* ptr);
        
        static constexpr uint64 max_node_depth = 20;
        static constexpr uint64 smallest_possible_block_size = 512;
    private:


        struct HeapHeader
        {
            uint64  size = 0;
            uintptr item_in_free_list = 0;
        };

        void Initialize();
        void Destroy();
        
        
        static uint64 ArrayHeap::GetSizeToReserveForBlockHeaders(uint64 size);
        static uint64 ArrayHeap::GetTotalSizeToAllocate(uint64 size);
        static uint64 ArrayHeap::GetNumberOfBlockHeadersToAllocate(uint64 size, uint64 sizeOfSmallestPossibleBlock);
        static uint64 ArrayHeap::GetSizeOfSmallestPossibleBlock(uint64 size, uint64 maxDepth);
        static uint64 ArrayHeap::GetMaximumDepth(uint64 size);
        static uint64 ArrayHeap::GetBlockIndex(uint64 size,uint32 power_of_heap);

        HeapHeader* ArrayHeap::FindBuddy(HeapHeader* header);
        static bool ArrayHeap::CanMergeWithBuddy(HeapHeader* left, HeapHeader* right);
        HeapHeader* ArrayHeap::MergeWithBuddy(HeapHeader* left, HeapHeader* right);


        HeapHeader* GetSmallestBlockToSplit(int64 index);
        void CalculateNextLevelAllocationSize(uint64 size);
        void Split(HeapHeader& block_header);
        void InsertBlockIntoFreeList(HeapHeader& block_header);
        HeapHeader* PopHeaderFromFreeList(uint64 freelistIndex);
        void RemoveHeaderFromFreeList(HeapHeader* header);
        
        bool m_destroyed;
        uint64 m_heap_size;
        uint64 m_actual_size;
        uint32 m_power_of_heap;
        uintptr m_base;
        MemoryStack& m_allocator;
        std::array<HeapHeader*, max_node_depth + 1> m_free_list;

        friend class MemoryManager;
    };
}

#endif