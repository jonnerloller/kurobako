#include "testsystem.h"
#include <iostream>
namespace kurobako::engine
{

	void TestSystem::Init(SystemInfo & p)
	{

	}

	void TestSystem::OnAddToRuntime(SystemInfo & p)
	{
        std::cout << "TestSystem::OnAddToRuntime" << std::endl;
	}

	void TestSystem::OnRemoveFromRuntime(SystemInfo & p)
	{
        std::cout << "TestSystem::OnRemoveFromRuntime" << std::endl;
	}

	void TestSystem::OnPause(SystemInfo & p)
	{
        std::cout << "TestSystem::OnPause" << std::endl;
	}

	void TestSystem::OnUnPause(SystemInfo & p)
	{
        std::cout << "TestSystem::OnUnPause" << std::endl;
	}

	void TestSystem::OnFirstRun(SystemInfo & p)
	{
        std::cout << "TestSystem::OnFirstRun" << std::endl;
	}

    void TestSystem::OnStartFrameSync(SystemInfo &p)
    {
        std::cout << "TestSystem::OnStartFrameSync" << std::endl;
    }

    void TestSystem::OnEndFrameSync(SystemInfo& p)
    {
        std::cout << "TestSystem::OnEndFrameSync" << std::endl;
    }

	void TestSystem::OnRestart(SystemInfo & p)
	{
        std::cout << "TestSystem::OnRestart" << std::endl;
	}

	void TestSystem::OnUpdate(SystemInfo& p)
	{
        std::cout << "TestSystem::OnUpdate" << std::endl;
	}

}