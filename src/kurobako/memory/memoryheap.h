#ifndef MEMORYHEAP_H
#define MEMORYHEAP_H
#include "types\sizedtypes.h"
namespace kurobako::memory
{
    // Thinking that we can use a memorystack at it's base.
    // Technique.
    // AllocateStack [sizeofHeap]
    // Each time we need to grab something from heap, allocate from stack (alignment pls)
    // Each time we need to delete somethign and return it to the heap, we throw it into a "linkedlist. you know.. the usual bs"
    // Idk if i want to handle arrays. maybe for arrays we force them to use Block Allocator. or use struct of array. we'll see.
    class MemoryHeap 
    {
        public:
        static atomic_uint32 m_unique_allocation_sizes;
        private:
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

    template <typename T>
    T* HeapAllocate()
    {
        // maybe some args?
        // need overload this for maximum arg value
        //T* obj = MemoryHeap:Allocate(GetHeapIndex<sizeof(T)>());
        //obj = new(T)()
    }

    template <typename T>
    void HeapDeallocate(T* obj)
    {
        //Call Destructor
        obj->~T();
        // return pointer so we can store it.
        MemoryHeap::Deallocate(GetHeapIndex<sizeof(T)>(),obj);
    }
}

#endif