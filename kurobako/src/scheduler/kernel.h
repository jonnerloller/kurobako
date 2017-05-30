#ifndef concurrency_kernel_h__
#define concurrency_kernel_h__

/*
	- spawns workers
	- informs them of the queues of other workers to steal from
*/

#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>

#include "deque.h"
#include "thread.h"
#include "worker.h"

namespace sandcastle::concurrency
{

	struct thread_info
	{
		size_t m_thread_id;
		worker_data m_data;
	};

	class kernel
	{
	public:

		static kernel& get()
		{
			static kernel singleton;
			return singleton;
		}

		void init(job* begin);
		void shutdown();

	private:

		static void launch_worker(thread_info data);

		unsigned int m_numthreads; //including main thread

		std::atomic<bool> m_stop;

		worker_data m_main_data;

		std::vector < std::thread > m_threadpool;
		std::vector < deque > m_queuepool;

		std::mutex m_sleeplock;
		std::mutex m_sleeplock_graphics;

		std::condition_variable m_sleep;
		std::condition_variable m_sleep_graphics;
	};

}

#endif