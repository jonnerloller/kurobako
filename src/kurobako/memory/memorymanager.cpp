#include "memorymanager.h"
namespace kurobako::memory
{
	//DECLARE_SINGLETON(MemoryManager);
	DEFINE_SINGLETON(MemoryManager);
    MemoryManager::MemoryManager(uint64 size)
    :	m_memory(size),
		m_stringbuffer(m_memory,STRING_BUFFER_SIZE)
    {

    }

    void MemoryManager::InitializeMemoryManager(uint64 size)
    {
       static MemoryManager *instance = ::new MemoryManager(size);
       SET_SINGLETON(MemoryManager,instance);
    }

	MemoryManager& MemoryManager::GetMemoryManager()
	{
		return *GET_SINGLETON(MemoryManager);
	}

	void MemoryManager::DestroyMemoryManager()
	{
		::delete GET_SINGLETON(MemoryManager);
	}

	char* MemoryManager::AllocateNonPersistentString(uint64 size)
	{
		return static_cast<char*>(m_stringbuffer.Allocate(size));
	}

	MemoryManager::~MemoryManager()
	{
	}
}