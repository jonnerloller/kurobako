#ifndef MEMORYSTACK_H
#define MEMORYSTACK_H
#include "types/sizedtypes.h"
#include "memorystats.h"
namespace kurobako::memory
{

    class MemoryStack
    {
        public:
            void* Allocate(uint64 size);

			void Deallocate(void* obj,uint64 size);
		
			void Reset();

			void Destroy();

			MemoryStack(uint64 size);
			MemoryStack(const MemoryStack& rhs) = delete;
			MemoryStack(MemoryStack&& rhs);
			MemoryStack& operator =(MemoryStack&& rhs);
            ~MemoryStack();

			const MemoryStats& GetStats() { return m_stats; }
			uint64 GetSize() { return m_size; }
        private:
            atomic_uintptr m_base;
            atomic_uintptr m_top;
			uint64 m_size;

			MemoryStats m_stats;
    };
}

#endif