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
        void  Deallocate();
        
    private:
        enum
        {
            HIGHEST_ORDER = 32,
        };

        struct ArrayHeapEntry
        {
            ArrayHeapEntry* left = nullptr;
            ArrayHeapEntry* right = nullptr;
            uint64          top = 0;
            uint64          size = 0;
        };

        static ArrayHeapEntry* AllocateArrayHeapEntry(uint64 base, uint64 size);
        static ArrayHeapEntry* SplitArrayHeap(ArrayHeapEntry* node);

        void Initialize();
        void Destroy();
        
        
        bool m_destroyed;
        uint64 m_size;
        atomic_uintptr m_base;
        ArrayHeapEntry m_root;
        MemoryStack& m_allocator;
        std::array<ArrayHeapEntry*, HIGHEST_ORDER> m_free_list;

        friend class MemoryManager;
    };
}

#endif