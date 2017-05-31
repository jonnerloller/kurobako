#include "logger.h"
#include "utility\globalsingletons.h"
#include <sstream>
#include <iostream>
namespace kurobako::log
{
	DEFINE_SINGLETON(Logger);
    void Logger::Log(const NonPersistentString& str, uint32 level)
    {
		std::cout << str.Get() << std::endl;
    }

    void Logger::Dump(cstr str)
    {

    }

    Logger::Logger():m_offset(0)
    {
        m_buffer[0] = 0;
    }

	Logger::~Logger()
    {
        
    }
}