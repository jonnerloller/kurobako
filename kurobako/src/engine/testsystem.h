#ifndef TESTSYSTEM_H
#define TESTSYSTEM_H
#include "system.h"
namespace kurobako::engine
{
	class TestSystem : System
	{
		virtual void Init(SystemInfo & p) final;
		virtual void OnAddToRuntime(SystemInfo & p) final;
		virtual void OnRemoveFromRuntime(SystemInfo & p) final;
		virtual void OnPause(SystemInfo & p) final;
		virtual void OnUnPause(SystemInfo & p) final;
		virtual void OnFirstRun(SystemInfo & p) final;
		virtual void OnRestart(SystemInfo & p) final;
		virtual void Update(SystemInfo& p) final;
	};
}
#endif // #ifndef TESTSYSTEM_H
