#ifndef MEMORYSTATS_H
#define MEMORYSTATS_H
#include "types\sizedtypes.h"
namespace kurobako::memory
{

	struct MemoryStats
	{
		#if !defined(KUROBAKOFINAL) && !defined(KUROBAKOPROFILE)
		uint64 m_sizeallocated;
		uint64 m_numallocations;
		uint64 m_numdeallocations;
		uint64 m_numcurrentallocated;
		MemoryStats();
		~MemoryStats();
		void Allocate(uint64 size);
		void Deallocate(uint64 size);
		#else
		void Allocate(uint64 size);
		void Deallocate(uint64 size);
		#endif	
		
	};

}
#endif