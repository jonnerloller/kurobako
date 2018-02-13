#include "memorymanager.h"
#include "memoryconstants.h"
#include <malloc.h>
namespace kurobako::memory
{
	static const uint32 alignment_size = 16;
	//DECLARE_SINGLETON(MemoryManager);
	DEFINE_SINGLETON(memory_manager);
    memory_manager::memory_manager(uint64 size)
    :	m_memory(size),
		m_stringbuffer(m_memory,STRING_BUFFER_SIZE),
		m_heap(m_memory,HEAP_BUFFER_SIZE),
        m_buddyheap(m_memory, BUDDY_HEAP_BUFFER_SIZE)
    {

    }

    void memory_manager::InitializeMemoryManager(uint64 size)
    {
       static memory_manager *instance = static_cast<memory_manager*>(_aligned_malloc(sizeof(memory_manager),DEFAULT_MEMORY_ALIGNMENT_SIZE));
	   instance = new(instance)memory_manager(size);
       SET_SINGLETON(memory_manager,instance);
    }

	void* memory_manager::AllocateSingleton(uint64 id,uint64 size)
	{
		return m_memory.allocate(size);
	}

	void memory_manager::DeallocateSingleton(void* obj, uint64 size)
	{
		m_memory.deallocate(obj, size);
	}

	memory_manager& memory_manager::GetMemoryManager()
	{
		return *GET_SINGLETON(memory_manager);
	}

	void memory_manager::DestroyMemoryManager()
	{
		_aligned_free(GET_SINGLETON(memory_manager));
	}

	void*	memory_manager::HeapAllocate(uint64 size, uint32 heapid)
	{
		return m_heap.Allocate(size, heapid);
	}
	void	memory_manager::HeapDeallocate(void* obj, uint32 heapid)
	{
		m_heap.Deallocate(obj, heapid);
	}

	char* memory_manager::AllocateNonPersistentString(uint64 size)
	{
		return static_cast<char*>(m_stringbuffer.allocate(size));
	}

	memory_manager::~memory_manager()
	{
	}
}