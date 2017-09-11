#ifndef concurrency_batch_h__
#define concurrency_batch_h__

#include <vector>
#include <atomic>

#include "job.h"
#include "counter.h"

namespace sandcastle::concurrency
{
	class batch : public job
	{
	public:

		batch();
		batch(job** job, size_t size = 1);

		void add(job** job, size_t size = 1);

	private:

		virtual void func() override;

		std::vector<job*> m_jobs;

	};
}

#endif