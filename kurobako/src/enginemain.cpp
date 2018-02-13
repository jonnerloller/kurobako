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
        constexpr uint64 allocation_size = static_cast<uint64>(4) << 30;
	    kurobako::memory::memory_manager::InitializeMemoryManager(allocation_size);
	
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
		kurobako::memory::memory_manager::DestroyMemoryManager();
	}
}