#ifndef LOGGER_H
#define LOGGER_H
#include <array>
#include "types/sizedtypes.h"
#include "types/nonpersistentstring.h"
#include <mutex>

#define LOG_INFO(str,level) GET_SINGLETON_SCOPED(kurobako::log,Logger)->Log(kurobako::NonPersistentString("%s(%d) [INFO] > %s",__FILE__,__LINE__,str.Get()),level)
#define LOG_ERROR(str,level) GET_SINGLETON_SCOPED(kurobako::log,Logger)->Log(kurobako::NonPersistentString("%s(%d) [ERROR] > %s",__FILE__,__LINE__,str.Get()),level)
#define LOG_DEBUG(str,level) GET_SINGLETON_SCOPED(kurobako::log,Logger)->Log(kurobako::NonPersistentString("%s(%d) [DEBUG] > %s",__FILE__,__LINE__,str.Get()),level)
namespace kurobako::log
{
    class Logger
    {
		enum
		{
			LOG_BUFFER_SIZE = 1 << 20
		};
        public:
        void Log(const NonPersistentString& str, uint32 level);
        void Dump(cstr str);

        Logger();
        ~Logger();
        private:
        std::array<byte,LOG_BUFFER_SIZE> m_buffer;
        uint64 m_offset;
        std::mutex m_logmutex;
    };
}

#endif