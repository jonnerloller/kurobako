#include "memoryheap.h"

namespace kurobako::memory
{
    atomic_uint32 MemoryHeap::m_unique_allocation_sizes = 0;
}