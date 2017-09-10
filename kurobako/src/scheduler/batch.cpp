#include "batch.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	batch::batch()
		: job(AFFINITY_NONE)
	{

	}

	batch::batch(job** job, size_t size)
		: job(AFFINITY_NONE)
	{
		add(job, size);
	}

  /*
    Waits for all elements of the batch job to complete. If the job is not
    running, does nothing
  */
	void batch::wait()
	{
    if (running() == false) {
      return;
    }

    while (m_ctr > 0) {
      this_thread::this_worker.run_one();
    }
	}

	void batch::add(job** j, size_t size)
	{
		if (j == nullptr)
			return;

		for (size_t i = 0; i < size; ++i) {
			job* t = j[i];

			m_jobs.push_back(t);
		}
	}

  /*
    Preps the counter that all jobs will notify
    runs each job asynchronously
    does *not* block until it is done. blocking is wrapped separately
  */
	void batch::func()
	{
    for (job* elem : m_jobs) {
      elem->notify_this(&m_ctr);
    }

    m_ctr = m_jobs.size();

    //assume that the jobs are already registered
    for (job* task : m_jobs) {
      task->detach();
    }
  }

}
