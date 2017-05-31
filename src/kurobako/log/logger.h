#ifndef LOGGER_H
#define LOGGER_H
#include <array>
#include "types/sizedtypes.h"
#include "types/nonpersistentstring.h"
#include <mutex>
namespace kurobako::log
{
    class Logger
    {
        enum
        {
            LOG_BUFFER_SIZE = 1 << 20;
        }
        public:
        void Log(cstr str);
        void Log(const NonPersistentString& str);
        void Dump(cstr str);

        Logger();
        ~Logger();
        private:
        std::array<byte> m_buffer[LOG_BUFFER_SIZE];
        uint64 m_offset;
        std::mutex m_logmutex;
    };
}

#endif