#include "enginemain.h"
#include "kurobakoconfig.h"
#include <iostream>
#include "../kurobako/memory/memorymanager.h"
#include "../kurobako/log/logger.h"
#include "../kurobako/types/sizedtypes.h"
#include "utility/singleton.h"
namespace kurobako::engine
{
    void InitEngine()
    {
        constexpr uint64 allocation_size = static_cast<uint64>(2) << 30;
	    kurobako::memory::MemoryManager::InitializeMemoryManager(allocation_size);
	    CREATE_SINGLETON_SCOPED(kurobako::log, Logger);
	
#if defined(KUROBAKODEBUG)
        std::cout << "Initializing Engine(Debug)" << std::endl;
#elif defined(KUROBAKORELEASE)
		std::cout << "Initializing Engine(Release)" << std::endl;
#elif defined(KUROBAKOPROFILE)
		std::cout << "Initializing Engine(Profile)" << std::endl;
#elif defined(KUROBAKOFINAL)
		std::cout << "Initializing Engine(Final)" << std::endl;
#endif
    }

	void DestroyEngine()
	{
		DESTROY_SINGLETON_SCOPE(kurobako::log, Logger);
		kurobako::memory::MemoryManager::DestroyMemoryManager();
	}
}