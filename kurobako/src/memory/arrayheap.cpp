#include "arrayheap.h"
#include "memorymanager.h"
#include "memorystack.h"
#include "./glm/glm.hpp"
namespace kurobako::memory
{
    uint64 GetNearestPower(uint64 num)
    {
        f32 num_log = log2(static_cast<f32>(num));
        return static_cast<uint64>(round(num_log));
    }
    uint64 GetOrder(uint64 num)
    {
        return static_cast<uint64>(log2(num));
    }

    ArrayHeap::ArrayHeap(MemoryStack& allocator, uint64 size)
        :m_allocator(allocator), m_size(GetNearestPower(size)), m_base(reinterpret_cast<uintptr>(allocator.Allocate(m_size))),m_destroyed(false)
    {

        m_root.top = m_base;
        m_root.size = size;

        for (auto &i : m_free_list)
        {
            i = nullptr;
        }

        m_free_list[GetOrder(m_size)] = &m_root;
    }

    ArrayHeap::~ArrayHeap()
    {
        Destroy();
    }

    ArrayHeap::ArrayHeapEntry* ArrayHeap::AllocateArrayHeapEntry(uint64 base, uint64 size)
    {
        ArrayHeapEntry* entry = memory::HeapNew<ArrayHeapEntry>("ArrayHeap");
        entry->top = base;
        entry->size = size;
        return entry;
    }

    ArrayHeap::ArrayHeapEntry* ArrayHeap::SplitArrayHeap(ArrayHeap::ArrayHeapEntry* node)
    {
        uint64 node_size = node->size << 1;
        uint64 left_base = node->top;
        uint64 right_base = left_base + node_size;
        node->left = AllocateArrayHeapEntry(left_base, node_size);
        node->right = AllocateArrayHeapEntry(right_base, node_size);
        return node;
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
        if (m_destroyed == false)
        {
            uintptr temp = m_base;
            m_allocator.Deallocate(reinterpret_cast<void*>(temp), m_size);
        }
    }
}