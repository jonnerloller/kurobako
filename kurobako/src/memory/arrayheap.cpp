#include "arrayheap.h"
#include "memorymanager.h"
#include "memorystack.h"
namespace kurobako::memory
{
    ArrayHeap::ArrayHeap(MemoryStack& allocator, uint64 size)
        :m_allocator(allocator), m_size(size), m_base(reinterpret_cast<uintptr>(allocator.Allocate(size))) , m_root(m_base,size)
    {
    }

    ArrayHeap::~ArrayHeap()
    {

    }

    ArrayHeap::ArrayHeapEntry* ArrayHeap::AllocateArrayHeapEntry(uint64 base, uint64 size)
    {
        ArrayHeapEntry* entry = memory::HeapNew<ArrayHeapEntry>("ArrayHeap");
        entry->top = base;
        entry->size = size;
        return entry;
    }

    ArrayHeap::ArrayHeapEntry* SplitArrayHeap(ArrayHeap::ArrayHeapEntry* node)
    {
        uint64 node_size = node->size << 1;
        uint64 left_base = node->top;
        uint64 right_base = left_base + offset;
        node->left = AllocateArrayHeapEntry(left_base, node_size);
        node->right = AllocateArrayHeapEntry(right_base, node_size);
    }


    void* ArrayHeap::Allocate(uint64 size)
    {
        return nullptr;
    }

    void ArrayHeap::Deallocate()
    {

    }

    void ArrayHeap::Initialize()
    {

    }

    void ArrayHeap::Destroy()
    {

    }

}