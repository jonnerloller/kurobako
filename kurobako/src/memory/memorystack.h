#ifndef MEMORYSTACK_H
#define MEMORYSTACK_H

#include "types\sizedtypes.h"

#include "memorystats.h"
namespace kurobako::memory
{
    class stack
    {
        public:
            void* allocate(uint64 size);
			void deallocate(void* obj,uint64 size);

			void destroy();

			stack(uint64 size);
			stack(const stack& rhs) = delete;
			stack(stack&& rhs);
			stack& operator =(stack&& rhs);
            ~stack();

			const stats& GetStats() { return m_stats; }
			uint64 GetSize() { return m_size; }
        private:
            atomic_uintptr m_base;
            atomic_uintptr m_top;
			uint64 m_size;

			stats m_stats;
    };
}

#endif