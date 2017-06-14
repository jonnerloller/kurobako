#ifndef MEMORYBUFFER_H
#define MEMORYBUFFER_H
#include "types/sizedtypes.h"
namespace kurobako::memory
{
    class MemoryStack;

    // Legit this should only be used for non persistant chars.
    class CircularMemoryBuffer
    {
        public:
		CircularMemoryBuffer(MemoryStack& allocator, uint64 size);
        ~CircularMemoryBuffer();
        void Destroy();

		void Reset();
        void* Allocate(uint64 size);
        // Note that there's no Deallocate function.
        private:

        MemoryStack& m_allocator;
        uint64 m_size;
        atomic_uintptr m_base;
        atomic_uintptr m_current;
        bool m_destroyed;
    };
}

#endif