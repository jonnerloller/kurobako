#include "runtime.h"
#include "system.h"
#include "scheduler/thread.h"
#include <algorithm>
namespace kurobako::engine
{
    Runtime::Runtime()
    {
    }
    void Runtime::Init()
    {

    }

    void Runtime::AddSystem(System* system)
    {
        m_Systems.push_back(system);
        system->OnAddToRuntime(SystemInfo());
    }

    void Runtime::RemoveSystem(System* system)
    {
        auto it = std::find(m_Systems.begin(),m_Systems.end(),system);
        if (it != m_Systems.end())
        {
            system->OnRemoveFromRuntime(SystemInfo());
            m_Systems.erase(std::remove(m_Systems.begin(),m_Systems.end(),system),m_Systems.end());
        }
    }

    void Runtime::Pause()
    {
        for (auto system : m_Systems)
        {
            system->OnPause(SystemInfo());
        }
    }

    void Runtime::UnPause()
    {
        for (auto system : m_Systems)
        {
            system->OnUnPause(SystemInfo());
        }
    }

    void Runtime::Restart()
    {
        for (auto system : m_Systems)
        {
            system->OnRestart(SystemInfo());
        }
    }

    void Runtime::StartFrameSync()
    {
        for (auto system : m_Systems)
        {
            system->OnStartFrameSync(SystemInfo());
        }
    }

    void Runtime::EndFrameSync()
    {
        for (auto system : m_Systems)
        {
            system->OnEndFrameSync(SystemInfo());
        }
    }

    void Runtime::func()
    {
        clear();
        for (auto system : m_Systems)
        {
            push_back(system);
        }
        chain::func();
    }
}