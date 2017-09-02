#ifndef ENGINECONTEXT_H
#define ENGINECONTEXT_H

namespace kurobako::engine
{
	class Engine;
    class Runtime;
	class EngineContext
	{
	public:
		Engine* m_Engine;
		Runtime* m_Runtime;
	private:
	};
}

#endif