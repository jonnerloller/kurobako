#include "memorystats.h"
namespace kurobako::memory
{
#if !defined(KUROBAKOFINAL) && !defined(KUROBAKOPROFILE)
	MemoryStats::MemoryStats()
		:m_sizeallocated(0),
		m_numallocations(0),
		m_numcurrentallocated(0),
		m_numdeallocations(0)
	{
	}
	void MemoryStats::Allocate(uint64 size)
	{
		m_sizeallocated += size;
		m_numallocations++;
		m_numcurrentallocated++;
	}
	void MemoryStats::Deallocate(uint64 size)
	{
		m_sizeallocated -= size;
		m_numdeallocations++;
		m_numcurrentallocated--;
	}
	MemoryStats::~MemoryStats()
	{

	}
#else
	void MemoryStats::Allocate(uint64 size) {}
	void MemoryStats::Deallocate(uint64 size) {}
#endif	
}