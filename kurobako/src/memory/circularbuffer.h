#ifndef MEMORYBUFFER_H
#define MEMORYBUFFER_H
#include "types/sizedtypes.h"
namespace kurobako::memory
{
    class stack;

    // Legit this should only be used for non persistant chars.
    class circular_buffer
    {
        public:
		circular_buffer(stack& allocator, uint64 size);
        ~circular_buffer();
        void destroy();

		void reset();
        void* allocate(uint64 size);
        // Note that there's no Deallocate function.
        private:

        stack& m_allocator;
        uint64 m_size;
        atomic_uintptr m_base;
        atomic_uintptr m_current;
        bool m_destroyed;
    };
}

#endif