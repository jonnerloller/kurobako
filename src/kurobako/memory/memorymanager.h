#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "types\sizedtypes.h"
#include "utility\singleton.h"
#include "utility\globalsingletons.h"
#include "memorystack.h"
#include "circularmemorybuffer.h"
#include "memoryheap.h"
#include "memoryconstants.h"
namespace kurobako::memory
{
    class MemoryManager
    {
        enum
        {
            STRING_BUFFER_SIZE = 1 << 20,
			HEAP_BUFFER_SIZE = 1 << 30
        };
        public:

        MemoryManager(uint64 size);
        MemoryManager(const MemoryManager& rhs) = delete;
        MemoryManager::~MemoryManager();

        static void InitializeMemoryManager(uint64 size);
        static MemoryManager& GetMemoryManager();
        static void DestroyMemoryManager();

		void*	AllocateSingleton(uint64 id, uint64 size);
		void	DeallocateSingleton(void* obj, uint64 size);

		void*	HeapAllocate(uint64 size, uint32 heapid);
		void	HeapDeallocate(void* obj, uint32 heapid);
        char*	AllocateNonPersistentString(uint64 size);
        private:
        MemoryStack m_memory;
        CircularMemoryBuffer m_stringbuffer;




		//Heap should definitely come last. seriously.
		MemoryHeap m_heap;
    };

	template <typename T>
	T* HeapAllocate(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::MemoryManager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)>()));
	#ifdef MEMORY_TAGGING_ENABLED
		uintptr addr_of_header = reinterpret_cast<uintptr>(ret) - sizeof(MemoryHeap::MemoryHeader);
		MemoryHeap::MemoryHeader* header = reinterpret_cast<MemoryHeap::MemoryHeader*>(addr_of_header);
		header->m_top.used_when_allocated = MemoryHeap::MemoryHeader::MemoryPattern::MEMORY_PATTERN_ALLOCATED;
		header->m_btm.userdata = memtag;
	#endif // MEMORY
		ret = new(ret)T();
		return ret;
	}

	template <typename T>
	void HeapDeallocate(T* obj)
	{
		//Call Destructor
		obj->~T();
#ifdef MEMORY_TAGGING_ENABLED
		uintptr addr_of_header = reinterpret_cast<uintptr>(obj) - sizeof(MemoryHeap::MemoryHeader);
		MemoryHeap::MemoryHeader* header = reinterpret_cast<MemoryHeap::MemoryHeader*>(addr_of_header);
		header->m_top.nextdata = 0;
		header->m_btm.used_when_freed = MemoryHeap::MemoryHeader::MemoryPattern::MEMORY_PATTERN_DEALLOCATED;
#endif // MEMORY
		// return pointer so we can store it.
		kurobako::memory::MemoryManager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
	}

  #include "memorymanager.hpp"
}

#endif