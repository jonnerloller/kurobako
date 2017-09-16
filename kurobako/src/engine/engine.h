#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include "scheduler/batch.h"
namespace kurobako::engine
{
	class Runtime;

    // Generally speaking, we are only going to have 1 Runtime.
	class Engine : public sandcastle::concurrency::batch
	{
		
	public:
        void AddRuntime(Runtime* runtime);
        void Update();
        void StartFrameSync();
        void EndFrameSync();
    protected:
        virtual void func() final;
	private:
        Runtime* test;
		std::vector<Runtime*> m_Runtimes;
	};
}

#endif