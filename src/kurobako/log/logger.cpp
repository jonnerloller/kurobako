#include "logger.h"

namespace kurobako::log
{
    void Log(cstr str)
    {
        int strlen = strlen(str) + 1;
        if(m_offset + strlen < LOG_BUFFER_SIZE)
        {
            strcpy_s(&m_buffer[m_offset],strlen,str);
            m_offset += strlen;
        }
        // figure out how to put timestamp.
    }

    void Log(const NonPersistentString& str)
    {

    }

    void Dump(cstr str)
    {

    }

    Logger():m_offset(0)
    {
        m_buffer[0] = 0;
    }

    ~Logger()
    {
        
    }
}