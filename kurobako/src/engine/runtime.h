#ifndef RUNTIME_H
#define RUNTIME_H
#include <vector>
#include "scheduler/chain.h"
namespace kurobako::engine
{
	//// Called after every System / Component has already been constructed.
	//virtual void OnPause(SystemInfo & p) = 0;
	//virtual void OnUnPause(SystemInfo & p) = 0;
	//virtual void OnFirstRun(SystemInfo & p) = 0;
	//virtual void OnRestart(SystemInfo & p) = 0;
	//virtual void Update(SystemInfo& p) = 0;

    // We decide that we update in the order of systems added, so kind of like a chain.
    // We assume that systems will create jobs of batches
	class System;
	class Runtime : public sandcastle::concurrency::chain
	{
	public:
        Runtime();
		void Init();
		void AddSystem(System* system);
		void RemoveSystem(System* system);
		void Pause();
		void UnPause();
		void Restart();
		void StartFrameSync();
		void EndFrameSync();
    protected:
        virtual void func() override;
    private:

	//private:
		std::vector<System*> m_Systems;
	};
}

#endif
