#ifndef MEMORYHEAP_H
#define MEMORYHEAP_H
#include "types\sizedtypes.h"
#include "memorystats.h"
#include <array>
namespace kurobako::memory
{
	class MemoryStack;
    // Thinking that we can use a memorystack at it's base.
    // Technique.
    // AllocateStack [sizeofHeap]
    // Each time we need to grab something from heap, allocate from stack (alignment pls)
    // Each time we need to delete somethign and return it to the heap, we throw it into a "linkedlist. you know.. the usual bs"
    // Idk if i want to handle arrays. maybe for arrays we force them to use Block Allocator. or use struct of array. we'll see.
    class MemoryHeap 
    {
        // The MemoryHeader that we will be using for objects in our heap
        // Please note that only objects constructed by the heap will have a header.
        // Because with our stack allocator, we need to know the order anyway
        // and with our block allocator, we'lll be allocating from the heap so it doesn't really matter
	public:
        struct MemoryHeader
        {
			enum class MemoryPattern : uint64
			{
				MEMORY_PATTERN_ALLOCATED = 0xCDCDCDCDCDCDCDCD,
				MEMORY_PATTERN_DEALLOCATED = 0xEFEFEFEFEFEFEFEF
			};
            // we need a pointer to point to the next available data.
            // once allocated what should this be?
            // I can think that perhaps we can use this as some enum or something?
            // like a type id
            // regardless... this needs to be 16 bytes.
            union
            {
				MemoryPattern used_when_allocated;
                uintptr nextdata;
            } m_top;
            // When allocated... userData should clearly be a form of tagging data.
            // When deallocated... what should userData be?
            union
            {
				MemoryPattern used_when_freed;
                cstr userdata;
            } m_btm;
        };
	private:
        enum
        {
            NUM_MAX_HEAP_TYPES = 256,
        };
	public:
        static atomic_uint32 m_unique_allocation_sizes;


		MemoryHeap(MemoryStack& allocator, uint64 size);
        ~MemoryHeap();
        void* Allocate(uint64 size, uint32 heapid);
		void Deallocate(void* obj,uint32 heapid);

        private:
			void Destroy();

        atomic_uintptr m_base;
        atomic_uintptr m_top;
        uint64 m_size;
		MemoryStack& m_allocator;
        
        std::array<atomic_uintptr,NUM_MAX_HEAP_TYPES> m_heaplist;
		bool m_destroyed;

		MemoryStats m_stats;
    };

    template <uint32 N>
    uint32 GetHeapIndex()
    {
        static uint32 index = kurobako::memory::MemoryHeap::m_unique_allocation_sizes.fetch_add(1);
        return index;
    }

    template <typename T>
    uint32 RegisterHeap()
    {
        return GetHeapIndex<sizeof(T)>();
    }
}

#endif