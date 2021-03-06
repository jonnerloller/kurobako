#include "enginemain.h"
#include "kurobakoconfig.h"
#include <iostream>
#include "memory/memorymanager.h"
#include "log/logger.h"
#include "types/sizedtypes.h"
#include "utility/singleton.h"
namespace kurobako::engine
{
    void InitEngine()
    {
        constexpr uint64 allocation_size = static_cast<uint64>(2) << 30;
	    kurobako::memory::MemoryManager::InitializeMemoryManager(allocation_size);
	    CREATE_SINGLETON_SCOPED(kurobako::log, Logger);
	
#if defined(KBK_DEBUG)
        std::cout << "Initializing Engine(Debug)" << std::endl;
#elif defined(KBK_RELEASE)
		std::cout << "Initializing Engine(Release)" << std::endl;
#elif defined(KBK_PROFILE)
		std::cout << "Initializing Engine(Profile)" << std::endl;
#elif defined(KBK_FINAL)
		std::cout << "Initializing Engine(Final)" << std::endl;
#endif
    }
	void DestroyEngine()
	{
		DESTROY_SINGLETON_SCOPE(kurobako::log, Logger);
		kurobako::memory::MemoryManager::DestroyMemoryManager();
	}
}