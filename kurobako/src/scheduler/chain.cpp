#include "chain.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	chain::chain()
	{
	}

	void chain::push_back(job * j)
	{
		if (j) {
			m_jobs.push_back(j);
		}
	}

	void chain::clear()
	{
		m_jobs.clear();
	}

	void chain::func()
	{
		for (job* const j : m_jobs) {
			j->run();
		}
	}
}
