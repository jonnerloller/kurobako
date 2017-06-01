#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "types\sizedtypes.h"
#include "utility\singleton.h"
#include "utility\globalsingletons.h"
#include "memorystack.h"
#include "circularmemorybuffer.h"
namespace kurobako::memory
{
    class MemoryManager
    {
        enum
        {
            STRING_BUFFER_SIZE = 1 << 20
        };
        public:

        MemoryManager(uint64 size);
        MemoryManager(const MemoryManager& rhs) = delete;
        MemoryManager::~MemoryManager();

        static void InitializeMemoryManager(uint64 size);
        static MemoryManager& GetMemoryManager();
        static void DestroyMemoryManager();

        char* void AllocateNonPersistentString(uint64 size);
        private:
        MemoryStack m_memory;
        CircularMemoryBuffer m_stringbuffer;
    };

  #include "memorymanager.hpp"
}

#endif