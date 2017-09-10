#include "scheduler/job.h"
#include "scheduler/kernel.h"
#include "scheduler/chain.h"
#include "enginejobs.h"
#include "runtimejobs.h"
#include <iostream>
#include <array>

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
    struct SomeOtherJob : sandcastle::concurrency::job
    {
      SomeOtherJob(std::atomic<int>& counter)
        :m_ctr(counter)
      {}

      virtual void func() override
      {
        ++m_ctr;
        std::cout << m_ctr << std::endl;
      }

    private:
      std::atomic<int>& m_ctr;
    }

  public:

    virtual void func() override
    {
      // TODO: create job/batch/chain. and then print them
      using namespace sandcastle::concurrency;

      std::atomic<int> counter;

      std::array<SomeOtherJob> job_arr = {
        SomeOtherJob(counter), SomeOtherJob(counter),
        SomeOtherJob(counter), SomeOtherJob(counter),
        SomeOtherJob(counter)
      };

      std::cout << counter << std::endl;

      batch bat;
      for (const SomeOtherJob& elem : job_arr) {
        bat.add(&elem);
      }

      bat.run();
      bat.wait();
    }

  };

  void BeginMainLoop()
  {
    using kernel = sandcastle::concurrency::kernel;
    using job    = sandcastle::concurrency::job;

    kernel& scheulder = kernel::get();
    scheulder.init(&StartJob());
  }
}
