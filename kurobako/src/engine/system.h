#ifndef SYSTEM_H
#define SYSTEM_H
namespace kurobako::engine
{
	// this is just a generic thing. I don't know what I inted to put here yet.
	struct SystemInfo
	{

	};

	class System
	{


		// Called after every System / Component has already been constructed.
		virtual void Init(SystemInfo & p)					= 0;
		virtual void OnAddToRuntime(SystemInfo & p)			= 0;
		virtual void OnRemoveFromRuntime(SystemInfo & p)	= 0;
		virtual void OnPause(SystemInfo & p)				= 0;
		virtual void OnUnPause(SystemInfo & p)				= 0;
		virtual void OnFirstRun(SystemInfo & p)				= 0;
		virtual void OnRestart(SystemInfo & p)				= 0;
		virtual void Update(SystemInfo& p)					= 0;
	};
}
#endif
