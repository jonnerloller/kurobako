#include "job.h"
#include "thread.h"
#include <algorithm>

namespace sandcastle::concurrency
{
	job::job(worker_affinity affinity)
		: m_running(false)
		, m_affinity(affinity)
		, m_ctrs()
	{
	}

	void job::detach()
	{
		m_running = true;
		m_done    = false;

		this_thread::this_worker.submit_job(this);
	}

	worker_affinity job::affinity() const
	{
		return m_affinity;
	}

	void job::run()
	{
		m_running = true;
		m_done    = false;

		func();

		for (counter* const ctr : m_ctrs) {
			--(*ctr);
		}

		m_running = false;
		m_done    = true;
	}

	bool job::done() const
	{
		return m_done;
	}

  void job::notify_this(counter* ctr)
  {
    auto match_ptr = [ctr](counter* c) {
      return ctr == c;
    };

    if (ctr && std::none_of(m_ctrs.begin(), m_ctrs.end(), match_ptr)) {
      m_ctrs.push_back(ctr);
    }
  }

	void job::reset_notify_list()
	{
		m_ctrs.clear();
	}
}
