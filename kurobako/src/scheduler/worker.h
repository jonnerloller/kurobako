#ifndef concurrency_worker_h__
#define concurrency_worker_h__

#include <atomic>
#include <vector>
#include <condition_variable>

#include "job.h"
#include "deque.h"

namespace sandcastle::concurrency
{
	struct worker_data
	{
		deque* m_work;              //this thread's queue
		deque* m_graphics;          //== m_work if graphics worker

		std::vector<deque*> m_steal;
		std::atomic<bool>*  m_stop;

		std::condition_variable* m_sleep;
		std::condition_variable* m_sleepgraphics; //== m_sleepgraphics if graphics worker

		std::mutex* m_sleeplock;
	};

	class worker
	{
	public:

		void init(const worker_data& info);

		void run();
		bool run_one();

		void submit_job(job* job);

	private:

		job* collect_job();

		worker_data m_data;
	};

}

#endif
