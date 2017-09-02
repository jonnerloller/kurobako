#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
namespace kurobako::engine
{
	class Runtime;
	class Engine
	{
		
	public:
	private:
		std::vector<Runtime*> m_Runtimes;
	};
}

#endif