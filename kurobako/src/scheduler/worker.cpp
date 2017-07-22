#include "worker.h"

#include <cassert>
#include <thread>

namespace sandcastle::concurrency
{
	void worker::init(const worker_data& info)
	{
		assert(info.m_work);
		assert(info.m_stop);

		m_data = info;
	}

	void worker::run()
	{
		while (m_data.m_stop->load() == false)
		{
			if (run_one() == false)
			{
				std::unique_lock<std::mutex> lock(*m_data.m_sleeplock);
				m_data.m_sleep->wait(lock);
			}
		}
	}

	bool worker::run_one()
	{
		job* task = nullptr;

		if (task = collect_job())
		{
			task->run();

			return true;
		}

		return false;
	}

	void worker::submit_job(job* task)
	{
		if (task == nullptr)
			return;

		if (task->affinity() == AFFINITY_GRAPHICS)
		{
			m_data.m_graphics->push(task);
			m_data.m_sleepgraphics->notify_one();
		}
		else
		{
			m_data.m_work->push(task);
			m_data.m_sleep->notify_one();
		}

	}

	job* worker::collect_job()
	{
		job* task = m_data.m_work->pop();

		if (task)
			return task;
		else
		{
			for (deque* elem : m_data.m_steal)
			{
				if (task = elem->steal())
					return task;
			}
		}

		return nullptr;
	}

}