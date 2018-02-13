#ifndef MEMORYSTATS_H
#define MEMORYSTATS_H
#include "types\sizedtypes.h"
namespace kurobako::memory
{

	struct stats
	{
		#if !defined(KBK_FINAL) && !defined(KBK_PROFILE)
		uint64 m_sizeallocated;
		uint64 m_numallocations;
		uint64 m_numdeallocations;
		uint64 m_numcurrentallocated;
		stats();
		~stats();
		void allocate(uint64 size);
		void Deallocate(uint64 size);
		#else
		void allocate(uint64 size);
		void Deallocate(uint64 size);
		#endif	
		
	};

}
#endif