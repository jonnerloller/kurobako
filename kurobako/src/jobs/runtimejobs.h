#ifndef RUNTIMEJOBS_H
#define RUNTIMEJOBS_H
#include "scheduler/job.h"
#include "scheduler/kernel.h"
#include "scheduler/chain.h"
#include "scheduler/batch.h"
namespace kurobako::jobs
{
	class RuntimeInitJob : public sandcastle::concurrency::job
	{
	public:
		virtual void func() final;
	};

	class RuntimePauseBatch : public sandcastle::concurrency::batch
	{
	public:
		void init() ;
	};

	class RuntimeUnpauseBatch : public sandcastle::concurrency::batch
	{
	public:
		void init() ;
	};

	class RuntimeUpdateBatch : public sandcastle::concurrency::batch
	{
	public:
		void init() ;
	};

	class RuntimeStartFrameSyncJob : public sandcastle::concurrency::job
	{
	public:
		virtual void func() final;
	};

	class RuntimeEndFrameSyncJob : public sandcastle::concurrency::job
	{
	public:
		virtual void func() final;
	};

	class RuntimeLoopJob : public sandcastle::concurrency::job
	{
	public:
        virtual void func() final;
	};

    class TestJob : public sandcastle::concurrency::chain
    {
    public:
        virtual void func() final;
    };


	class RuntimeLoopChain : public sandcastle::concurrency::chain
	{
	public:
		static void PrepareFrame();
	};
}

#endif