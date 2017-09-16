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
		batch(job** j, size_t size = 1);

		void add(job** j, size_t size = 1);
        void push_back(job* j);
        void clear();

    protected:
        virtual void func() override;
	private:

		std::vector<job*> m_jobs;

	};
}

#endif