#include "scheduler/job.h"
#include "scheduler/kernel.h"
#include "scheduler/chain.h"
#include "enginejobs.h"
#include "runtimejobs.h"
#include <iostream>

namespace kurobako::jobs
{
	// so we want to basically want to mix batches and chains here and dump them in from here.
	class StartJob : public sandcastle::concurrency::job
	{

	public:
		virtual void func() override
		{
            static RuntimeLoopJob startJob;
            RuntimeLoopChain::PrepareFrame();
            sandcastle::concurrency::this_thread::this_worker.submit_job(&startJob);
		}
	};

  class SomeJob : public sandcastle::concurrency::job
  {
  public:

    virtual void func() override
    {
      // TODO: create job/batch/chain. and then print them
    }

  };

	void BeginMainLoop()
	{
		using kernel = sandcastle::concurrency::kernel;
		using job = sandcastle::concurrency::job;

		kernel& scheulder = kernel::get();
		scheulder.init(&StartJob());
	}
}
