#include <thread>
#include <utility>

#include "kernel.h"

namespace sandcastle::concurrency
{
	void kernel::init(job* startjob)
	{
		m_numthreads = std::thread::hardware_concurrency();

		m_threadpool.resize(m_numthreads - 1);
		m_queuepool.resize(m_numthreads);

		//m_queuepool[0] is ALWAYS graphics thread
		m_main_data.m_stop		= &m_stop;
		m_main_data.m_sleeplock	= &m_sleeplock_graphics;
		m_main_data.m_graphics	= m_main_data.m_work			= &m_queuepool[0];
		m_main_data.m_sleep		= m_main_data.m_sleepgraphics	= &m_sleep_graphics;

		for (auto& elem : m_queuepool) {
			if (&elem == m_main_data.m_work)
				continue;

			m_main_data.m_steal.push_back(&elem);
		}

		//other workers
		for (size_t i = 1; i < m_threadpool.size(); ++i) {
			worker_data data;
			data.m_stop				= &m_stop;
			data.m_work				= &m_queuepool[i];
			data.m_sleep			= &m_sleep;
			data.m_sleeplock		= &m_sleeplock;
			data.m_graphics			= m_main_data.m_graphics;
			data.m_sleepgraphics	= m_main_data.m_sleepgraphics;

			for (size_t j = 0; j < m_queuepool.size(); ++j) {
				if (data.m_work == &m_queuepool[j])
					continue;

				data.m_steal.push_back(&m_queuepool[j]);
			}

			thread_info info;
			info.m_data = data;
			info.m_thread_id = i;

			m_threadpool[i] = std::move(std::thread(&kernel::launch_worker, info));
		}

		//main worker info
		this_thread::thread_id = 0;
		this_thread::this_worker.init(m_main_data);
		this_thread::this_worker.submit_job(startjob);
		this_thread::this_worker.run();
	}

	void kernel::shutdown()
	{
		m_stop.store(true);

		for (auto& thread : m_threadpool) {
			thread.join();
		}
	}

	void kernel::launch_worker(thread_info data)
	{
		this_thread::thread_id = data.m_thread_id;
		this_thread::this_worker.init(data.m_data);

		this_thread::this_worker.run();
	}

}
