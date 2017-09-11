#include "job.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	job::job(worker_affinity affinity)
		: m_running(false)
		, m_affinity(affinity)
		, m_notifylist(0)
        , m_ctr(0)
	{
	}

	void job::detach()
	{
		m_running = true;
		m_done = false;

		this_thread::this_worker.submit_job(this);
	}

	worker_affinity job::affinity() const
	{
		return m_affinity;
	}

    void job::wait()
    {
        while (m_ctr > 0)
        {
            this_thread::this_worker.run_one();
        }
    }

	void job::run()
	{
		m_running = true;
		m_done = false;

		func();

		for (counter* ctr : m_notifylist)
		{
			--(*ctr);
		}

		m_running = false;
		m_done = true;
	}

	bool job::done() const
	{
		return m_done;
	}

	void job::notify(counter * ctr)
	{
		if (ctr)
            m_notifylist.push_back(ctr);
	}

	void job::reset_notify_list()
	{
        m_notifylist.clear();
	}
}