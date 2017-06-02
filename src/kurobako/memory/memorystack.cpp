#include "memorystack.h"
#include <cstdlib>
#include <assert.h>
#include "memoryconstants.h"
#include <malloc.h>
namespace kurobako::memory
{
	void* MemoryStack::Allocate(uint64 size)
	{
#ifdef MEMORY_ALIGNMENT_ENABLED
		size = AlignSizeTo16(size);
#endif
		#if defined(KUROBAKODEBUG)||defined(KUROBAKORELEASE)
		uintptr newtop = m_top + size;
		uintptr maxtop = m_base + m_size;
		assert(newtop < maxtop);
		#endif	
		m_stats.Allocate(size);
		uintptr temp = m_top.fetch_add(size);
		return reinterpret_cast<void*>(temp);
	}

	void MemoryStack::Deallocate(void* obj, uint64 size)
	{
#ifdef MEMORY_ALIGNMENT_ENABLED
		size = AlignSizeTo16(size);
#endif
		#if defined(KUROBAKODEBUG) ||defined(KUROBAKORELEASE)
		uintptr estimatedbase = m_top - size;
		uintptr currentbase = reinterpret_cast<uintptr>(obj);
		assert(estimatedbase == currentbase);
		
		#endif	
		m_stats.Deallocate(size);
		m_top -= size;
	}

	void MemoryStack::Reset()
	{
		uintptr temp = m_base;
		m_top = temp;
	}

	void MemoryStack::Destroy()
	{
		uintptr temp = m_base;
		_aligned_free(reinterpret_cast<void*>(temp));
		m_base = 0;
		m_top = 0;
		m_size = 0;
	}

	MemoryStack::MemoryStack(uint64 size)
		:m_size(size)
	{
		m_base = reinterpret_cast<uintptr>(_aligned_malloc(size,DEFAULT_MEMORY_ALIGNMENT_SIZE));
		uintptr temp = m_base;
		m_top = temp;
	}

	MemoryStack::MemoryStack(MemoryStack&& rhs)
		:m_base(0),m_top(0)
	{
		
	}

	MemoryStack& MemoryStack::operator =(MemoryStack&& rhs)
	{
		return *this;
	}

    MemoryStack::~MemoryStack()
	{
		Destroy();
	}
}