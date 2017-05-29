#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "types\sizedtypes.h"
#include "utility\singleton.h"
#include "utility\globalsingletons.h"
#include "memorystack.h"
namespace kurobako::memory
{
    class MemoryManager
    {
        public:

        MemoryManager(uint64 size);
        MemoryManager(const MemoryManager& rhs) = delete;

        static void InitializeMemoryManager(uint64 size);
        static MemoryManager& GetMemoryManager();
        static void DestroyMemoryManager();

        private:
        MemoryStack m_memory;
    };
}

#endif