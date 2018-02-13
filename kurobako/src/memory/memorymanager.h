#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "types\sizedtypes.h"
#include "utility\singleton.h"
#include "utility\globalsingletons.h"
#include "memorystack.h"
#include "circularbuffer.h"
#include "memoryheap.h"
#include "memoryconstants.h"
#include "memoryheap.h"
#include <utility>
namespace kurobako::memory
{
    class memory_manager
    {
		public:
        enum
        {
            STRING_BUFFER_SIZE = 1 << 20,
			HEAP_BUFFER_SIZE = 1 << 30,
            BUDDY_HEAP_BUFFER_SIZE = 1 << 30
        };
        

        memory_manager(uint64 size);
        memory_manager(const memory_manager& rhs) = delete;
        memory_manager::~memory_manager();

        static void InitializeMemoryManager(uint64 size);
        static memory_manager& GetMemoryManager();
        static void DestroyMemoryManager();

		void*	AllocateSingleton(uint64 id, uint64 size);
		void	DeallocateSingleton(void* obj, uint64 size);

		void*	HeapAllocate(uint64 size, uint32 heapid);
		void	HeapDeallocate(void* obj, uint32 heapid);
        char*	AllocateNonPersistentString(uint64 size);

		inline circular_buffer& GetStringBuffer() { return m_stringbuffer; }
        private:
        stack m_memory;
        circular_buffer m_stringbuffer;

        //Heaps should definitely come last. seriously.
        heap m_heap;
        heap m_buddyheap;
		
		
    };

	template <typename T>
	T* HeapAllocate(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::memory_manager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)>()));
		heap::SetHeaderAllocatePattern(ret,cstr);
		return ret;
	}

	template <typename T>
	T* HeapNew(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::memory_manager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)>()));
		heap::SetHeaderAllocatePattern(ret,memtag);
		ret = new(ret)T();
		return ret;
	}

	template <typename T, typename ... Args>
	T* HeapNew(cstr memtag, Args&&... args)
	{
		T* ret = static_cast<T*>(kurobako::memory::memory_manager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)>()));
		heap::SetHeaderAllocatePattern(ret,cstr);
		ret = new(ret)T(std::forward<Args>(args)...);
		return ret;
	}
	

	template <typename T, int64 N>
	T* HeapAllocate(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::memory_manager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)*N>()));
		heap::SetHeaderAllocatePattern(ret, cstr);
		return ret;
	}

	template <typename T, int64 N>
	T* HeapNew(cstr memtag)
	{
		T* ret = static_cast<T*>(kurobako::memory::memory_manager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)*N>()));
		heap::SetHeaderAllocatePattern(ret, cstr);
		for(int64 i =0; i < N; ++i)
		{
			ret = new(ret+i)T();
		}
		return ret;
	}

	template <typename T, int64 N>
	T* HeapNew(cstr memtag,const T&obj)
	{
		T* ret = static_cast<T*>(kurobako::memory::memory_manager::GetMemoryManager().HeapAllocate(sizeof(T), GetHeapIndex<sizeof(T)*N>()));
		heap::SetHeaderAllocatePattern(ret, cstr);
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
		heap::SetHeaderDeallocatePattern(obj);
		// return pointer so we can store it.
		kurobako::memory::memory_manager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
	}

	template <typename T>
	void HeapDelete(T* obj)
	{
		//Call Destructor
		obj->~T();
		// return pointer so we can store it.
		kurobako::memory::memory_manager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
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
		kurobako::memory::memory_manager::GetMemoryManager().HeapDeallocate(obj,GetHeapIndex<sizeof(T)>());
	}

  #include "memorymanager.hpp"
}

#endif