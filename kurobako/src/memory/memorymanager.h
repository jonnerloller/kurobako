#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "types\sizedtypes.h"
#include "utility\singleton.h"
#include "utility\globalsingletons.h"
#include "memorystack.h"
#include "circularmemorybuffer.h"
#include "memoryheap.h"
#include "memoryconstants.h"
#include <utility>
namespace kurobako::memory
{
    class MemoryManager
    {
		public:
        enum
        {
            STRING_BUFFER_SIZE = 1 << 20,
			HEAP_BUFFER_SIZE = 1 << 30
        };
        

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

		inline CircularMemoryBuffer& GetStringBuffer() { return m_stringbuffer; }
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
		MemoryHeap::SetHeaderAllocatePattern(ret,cstr);
		return ret;
	}

	template <typename T>
	T* HeapNew(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::MemoryManager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)>()));
		MemoryHeap::SetHeaderAllocatePattern(retcstr);
		ret = new(ret)T();
		return ret;
	}

	template <typename T, typename ... Args>
	T* HeapNew(cstr memtag, Args&&... args)
	{
		T* ret = static_cast<T*>(kurobako::memory::MemoryManager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)>()));
		MemoryHeap::SetHeaderAllocatePattern(ret,cstr);
		ret = new(ret)T(std::forward<Args>(args)...);
		return ret;
	}
	

	template <typename T, int64 N>
	T* HeapAllocate(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::MemoryManager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)*N>()));
		MemoryHeap::SetHeaderAllocatePattern(ret, cstr);
		return ret;
	}

	template <typename T, int64 N>
	T* HeapNew(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::MemoryManager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)*N>()));
		MemoryHeap::SetHeaderAllocatePattern(ret, cstr);
		for(int64 i =0; i < N; ++i)
		{
			ret = new(ret+i)T();
		}
		return ret;
	}

	template <typename T, int64 N>
	T* HeapNew(cstr memtag,const T&obj)
	{
		T* ret = static_cast<T*>(kurobako::memory::MemoryManager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)*N>()));
		MemoryHeap::SetHeaderAllocatePattern(ret, cstr);
		ret = new(ret)T(obj);
		for(int64 i =0; i < N; ++i)
		{
			ret = new(ret+i)T(obj);
		}
		return ret;
	}

	template <typename T>
	void HeapDeallocate(T* obj)
	{
		MemoryHeap::SetHeaderDeallocatePattern(obj);
		// return pointer so we can store it.
		kurobako::memory::MemoryManager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
	}

	template <typename T>
	void HeapDelete(T* obj)
	{
		//Call Destructor
		obj->~T();
		// return pointer so we can store it.
		kurobako::memory::MemoryManager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
	}

	template <typename T, uint64 N>
	void HeapDelete(T* obj)
	{
		//Call Destructor
		for(int64 i=0; i < N; ++i)
		{
			(obj+i)->~T();
		}
		// return pointer so we can store it.
		kurobako::memory::MemoryManager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
	}

  #include "memorymanager.hpp"
}

#endif