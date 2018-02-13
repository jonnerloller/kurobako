#ifndef MEMORYCONSTANTS_H
#define MEMORYCONSTANTS_H
#include "types\sizedtypes.h"
namespace kurobako::memory
{
    static const uint32 DEFAULT_MEMORY_ALIGNMENT_SIZE = 16;

    #define KBK_MEMTAG

	inline uint64 AlignAddressTo(uintptr address, uint64 alignment)
	{
		//We can assume this will be never be 0, 0 is nullptr
		return ((address - 1) / alignment + 1) * alignment;
	}
	inline uint64 align_to_16(uint64 toalign)
	{
		return (((toalign - 1) / 16) + 1) * 16;
	}
}

#endif