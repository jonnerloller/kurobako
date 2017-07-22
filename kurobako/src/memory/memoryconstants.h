#ifndef MEMORYCONSTANTS_H
#define MEMORYCONSTANTS_H

namespace kurobako::memory
{
    static const uint32 DEFAULT_MEMORY_ALIGNMENT_SIZE = 16;
#ifdef KUROBAKODEBUG
	#define MEMORY_TAGGING_ENABLED
#endif
	#define MEMORY_ALIGNMENT_ENABLED

	inline uint64 AlignAddressTo(uintptr address, uint64 alignment)
	{
		//We can assume this will be never be 0, 0 is nullptr

		return ((address - 1) / alignment + 1) * alignment;
	}
	inline uint64 AlignSizeTo16(uint64 toalign)
	{
		return (((toalign - 1) / 16) + 1) * 16;
	}
}

#endif