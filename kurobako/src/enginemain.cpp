#include "enginemain.h"
#include "kurobakoconfig.h"
#include <iostream>
#include "memory/memorymanager.h"
#include "log/logger.h"
#include "types/sizedtypes.h"
#include "utility/singleton.h"
#include "engine/enginecontext.h"
#include "engine/engine.h"
#include "engine/testsystem.h"
#include "engine/runtime.h"
#include "scheduler/kernel.h"
#include "scheduler/batch.h"
namespace kurobako::engine
{
    void InitEngine()
    {
        constexpr uint64 allocation_size = static_cast<uint64>(2) << 30;
	    kurobako::memory::MemoryManager::InitializeMemoryManager(allocation_size);
	    CREATE_SINGLETON_SCOPED(kurobako::log, Logger);
		CREATE_SINGLETON_SCOPED(kurobako::engine, EngineContext);
		
		GET_SINGLETON(EngineContext)->m_Engine = memory::HeapNew<Engine>("Engine");

        Runtime* runtime = memory::HeapNew<Runtime>("Runtime1");
        System* system = memory::HeapNew<TestSystem>("Test System");
        runtime->AddSystem(system);


        GET_SINGLETON(EngineContext)->m_Engine->AddRuntime(runtime);
	
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
	void RunEngine()
	{
        using kernel = sandcastle::concurrency::kernel;
        using job = sandcastle::concurrency::job;

        kernel& scheulder = kernel::get();
        
        scheulder.init(GET_SINGLETON(EngineContext)->m_Engine);
	}

	void DestroyEngine()
	{
        memory::HeapDelete(GET_SINGLETON(EngineContext)->m_Engine);
         
		DESTROY_SINGLETON_SCOPE(kurobako::log, Logger);
		kurobako::memory::MemoryManager::DestroyMemoryManager();
	}
