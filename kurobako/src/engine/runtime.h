#ifndef RUNTIME_H
#define RUNTIME_H
#include <vector>
namespace kurobako::engine
{
	//// Called after every System / Component has already been constructed.
	//virtual void OnPause(SystemInfo & p) = 0;
	//virtual void OnUnPause(SystemInfo & p) = 0;
	//virtual void OnFirstRun(SystemInfo & p) = 0;
	//virtual void OnRestart(SystemInfo & p) = 0;
	//virtual void Update(SystemInfo& p) = 0;
	class System;
	class Runtime
	{
	public:
		void Init();
		void AddSystem(System* system);
		void RemoveSystem(System* system);
		void Pause();
		void UnPause();
		void Restart();
		void StartFrameSync();
		void EndFrameSync();
		void Update();

	//private:
		std::vector<System*> m_Systems;
	};
}

#endif
