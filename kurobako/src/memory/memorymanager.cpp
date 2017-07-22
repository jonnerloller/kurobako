#include "memorymanager.h"
#include "memoryconstants.h"
#include <malloc.h>
namespace kurobako::memory
{
	static const uint32 alignment_size = 16;
	//DECLARE_SINGLETON(MemoryManager);
	DEFINE_SINGLETON(MemoryManager);
    MemoryManager::MemoryManager(uint64 size)
    :	m_memory(size),
		m_stringbuffer(m_memory,STRING_BUFFER_SIZE),
		m_heap(m_memory,HEAP_BUFFER_SIZE)
    {

    }

    void MemoryManager::InitializeMemoryManager(uint64 size)
    {
       static MemoryManager *instance = static_cast<MemoryManager*>(_aligned_malloc(sizeof(MemoryManager),DEFAULT_MEMORY_ALIGNMENT_SIZE));
	   instance = new(instance)MemoryManager(size);
       SET_SINGLETON(MemoryManager,instance);
    }

	void* MemoryManager::AllocateSingleton(uint64 id,uint64 size)
	{
		return m_memory.Allocate(size);
	}

	void MemoryManager::DeallocateSingleton(void* obj, uint64 size)
	{
		m_memory.Deallocate(obj, size);
	}

	MemoryManager& MemoryManager::GetMemoryManager()
	{
		return *GET_SINGLETON(MemoryManager);
	}

	void MemoryManager::DestroyMemoryManager()
	{
		_aligned_free(GET_SINGLETON(MemoryManager));
	}

	void*	MemoryManager::HeapAllocate(uint64 size, uint32 heapid)
	{
		return m_heap.Allocate(size, heapid);
	}
	void	MemoryManager::HeapDeallocate(void* obj, uint32 heapid)
	{
		m_heap.Deallocate(obj, heapid);
	}

	char* MemoryManager::AllocateNonPersistentString(uint64 size)
	{
		return static_cast<char*>(m_stringbuffer.Allocate(size));
	}

	MemoryManager::~MemoryManager()
	{
	}
}