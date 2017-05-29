#include "memorymanager.h"
namespace kurobako::memory
{
	//DECLARE_SINGLETON(MemoryManager);
	DEFINE_SINGLETON(MemoryManager);
    MemoryManager::MemoryManager(uint64 size)
    :m_memory(size)
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
}