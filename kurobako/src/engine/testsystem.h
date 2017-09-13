#ifndef TESTSYSTEM_H
#define TESTSYSTEM_H
#include "system.h"
#include "types/sizedtypes.h"
namespace kurobako::engine
{
	class TestSystem : public System
	{

    public:
		virtual void Init(SystemInfo & p) final;
		virtual void OnAddToRuntime(SystemInfo & p) final;
		virtual void OnRemoveFromRuntime(SystemInfo & p) final;
		virtual void OnPause(SystemInfo & p) final;
		virtual void OnUnPause(SystemInfo & p) final;
		virtual void OnFirstRun(SystemInfo & p) final;
        virtual void OnStartFrameSync(SystemInfo &p)final;
        virtual void OnEndFrameSync(SystemInfo& p)final;
		virtual void OnRestart(SystemInfo & p) final;
		virtual void OnUpdate(SystemInfo& p) final;

    private:
        uint32 i = 0;
	};
}
#endif // #ifndef TESTSYSTEM_H
