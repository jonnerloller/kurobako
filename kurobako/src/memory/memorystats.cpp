#include "memorystats.h"
namespace kurobako::memory
{
#if !defined(KBK_FINAL) && !defined(KBK_PROFILE)
	stats::stats()
		:m_sizeallocated(0),
		m_numallocations(0),
		m_numcurrentallocated(0),
		m_numdeallocations(0)
	{
	}
	void stats::allocate(uint64 size)
	{
		m_sizeallocated += size;
		m_numallocations++;
		m_numcurrentallocated++;
	}
	void stats::Deallocate(uint64 size)
	{
		m_sizeallocated -= size;
		m_numdeallocations++;
		m_numcurrentallocated--;
	}
	stats::~stats()
	{

	}
#else
	void stats::allocate(uint64 size) {}
	void stats::Deallocate(uint64 size) {}
#endif	
}