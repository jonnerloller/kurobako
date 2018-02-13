#include "memorystack.h"
#include <cstdlib>
#include <assert.h>
#include "memoryconstants.h"
#include <malloc.h>
namespace kurobako::memory
{
	void* stack::allocate(uint64 size)
	{

		size = align_to_16(size);
		#if defined(KBK_DEBUG)||defined(KBK_RELEASE)
		uintptr newtop = m_top + size;
		uintptr maxtop = m_base + m_size;
		assert(newtop < maxtop);
		#endif	
		m_stats.allocate(size);
		uintptr temp = m_top.fetch_add(size);
		return reinterpret_cast<void*>(temp);
	}

	void stack::deallocate(void* obj, uint64 size)
	{

		size = align_to_16(size);
		#if defined(KBK_DEBUG) ||defined(KBK_RELEASE)
		uintptr estimated_base = m_top - size;
		uintptr current_base = reinterpret_cast<uintptr>(obj);
		assert(estimated_base == current_base);
		
		#endif	
		m_stats.Deallocate(size);
		m_top -= size;
	}

	void stack::destroy()
	{
		uintptr temp = m_base;
		_aligned_free(reinterpret_cast<void*>(temp));
		m_base = 0;
		m_top = 0;
		m_size = 0;
	}

	stack::stack(uint64 size)
		:m_size(size)
	{
		m_base = reinterpret_cast<uintptr>(_aligned_malloc(size,DEFAULT_MEMORY_ALIGNMENT_SIZE));
		uintptr temp = m_base;
		m_top = temp;
	}

	stack::stack(stack&& rhs)
		:m_base(0),m_top(0)
	{
		
	}

	stack& stack::operator =(stack&& rhs)
	{
		return *this;
	}

    stack::~stack()
	{
		destroy();
	}
}