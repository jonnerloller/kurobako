#include "batch.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	batch::batch()
		: job(AFFINITY_NONE)
	{

	}

	batch::batch(job** j, size_t size)
		: job(AFFINITY_NONE)
	{
		add(j, size);
	}

    void batch::clear()
    {
        m_jobs.clear();
        m_ctr = 0;
    }

	void batch::add(job** j, size_t size)
	{
		if (j == nullptr)
			return;

		for (size_t i = 0; i < size; ++i)
		{
			job* t = j[i];

			t->notify(&m_ctr);
			++m_ctr;

			m_jobs.push_back(t);
		}
	}

    void batch::push_back(job* j)
    {
        j->notify(&m_ctr);
        ++m_ctr;
        m_jobs.push_back(j);
    }

	void batch::func()
	{
		//assume that the jobs are already registered
		for (job* job : m_jobs)
		{
			this_thread::this_worker.submit_job(job);
		}
        wait();
	}
}