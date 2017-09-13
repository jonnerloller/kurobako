#include "engine.h"
#include "runtime.h"
#include "scheduler/thread.h"
namespace kurobako::engine
{
    void Engine::AddRuntime(Runtime* runtime)
    {
        m_Runtimes.push_back(runtime);
    }

    void Engine::Update()
    {
        clear();
        for (auto runtime : m_Runtimes)
        {
            push_back(runtime);
        }
    }
    void Engine::StartFrameSync()
    {
        for (auto runtime : m_Runtimes)
        {
            runtime->StartFrameSync();
        }
    }

    void Engine::EndFrameSync()
    {
        for (auto runtime : m_Runtimes)
        {
            runtime->EndFrameSync();
        }
    }

    void Engine::func()
    {
        clear();
        StartFrameSync();
        Update();
        EndFrameSync();
        batch::func();
        sandcastle::concurrency::this_thread::this_worker.submit_job(this);
    }
}