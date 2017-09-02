#include "runtimejobs.h"
#include "engine/enginecontext.h"
#include "engine/runtime.h"
#include "utility/globalsingletons.h"
#include <iostream>
#include "engine/system.h"
#include "types/sizedtypes.h"
#include <assert.h>
namespace kurobako::jobs
{
	static RuntimeInitJob sRuntimeInit;
	static RuntimePauseBatch sRuntimePause;
	static RuntimeUnpauseBatch sRuntimeUnpause;
	static RuntimeUpdateBatch sRuntimeUpdate;
	static RuntimeStartFrameSyncJob sRuntimeStartFrameSync;
	static RuntimeEndFrameSyncJob sRuntimeEndFrameSync;
	static RuntimeLoopChain sRuntimeLoop;
    static TestJob sTestJob;

    
    static atomic_int32 start;
    static atomic_int32 actual;
    static atomic_int32 target;

	void RuntimeInitJob::func()
	{
		engine::EngineContext* context = GET_SINGLETON_SCOPED(kurobako::engine,EngineContext);
		context->m_Runtime->Init();

		for (auto elem : context->m_Runtime->m_Systems)
		{
			//elem->Init();
		}
	}

	void RuntimePauseBatch::init()
	{

	}

	void RuntimeUnpauseBatch::init()
	{

	}

	void RuntimeUpdateBatch::init()
	{
       
	}

	void RuntimeStartFrameSyncJob::func()
	{
        start.store(actual.load());
		std::cout << "Start Frame Sync : " << start << std::endl;
        target.store(start.load() + 50);
	}

	void RuntimeEndFrameSyncJob::func()
	{
		std::cout << "End Frame Sync : " << target << std::endl;
        //assert(target.load() == actual.load());
	}

	void RuntimeLoopJob::func()
	{
        //sRuntimeLoop.PrepareFrame();

        // the actual chain that we want to run
        sandcastle::concurrency::this_thread::this_worker.submit_job(&sRuntimeLoop);

        // what creates the loop
        sandcastle::concurrency::this_thread::this_worker.submit_job(this);
	}

	void RuntimeLoopChain::PrepareFrame()
	{
		sRuntimeLoop.clear();

        // START
		sRuntimeLoop.push_back(&sRuntimeStartFrameSync);
		
        sandcastle::concurrency::job* arr[]
            =
        {
            &sTestJob,
            &sTestJob,
            &sTestJob,
            &sTestJob,
            &sTestJob
        };
         sRuntimeUpdate.add(arr,sizeof(arr)/sizeof(TestJob*));
        for (int i = 0; i < 10; ++i)
        {
            // BUNCH OF UPDATES
            sRuntimeLoop.push_back(&sRuntimeUpdate);
        }
		//sRuntimeLoop.push_back(&sRuntimeEndFrameSync);
	}

    void TestJob::func()
    {
        ++actual;
        std::cout << "UPDATE : " << actual << std::endl;
    }
}