#include "nonpersistentstring.h"
#include "utility\globalsingletons.h"
#include "memory\memorymanager.h"
#include <cstdarg>
namespace kurobako
{
    //NonPersistentString::NonPersistentString(const char* str)
    //:m_str(nullptr), m_strlen(0)
    //{
    //    Set(str);
    //}
    NonPersistentString::NonPersistentString(const char* format,...)
    :m_str(nullptr), m_strlen(0)
    {
        char str[MAX_STRING_SIZE];
        va_list argptr;
        va_start(argptr, format);
        vsprintf_s(str,MAX_STRING_SIZE, format, argptr);
        va_end(argptr);
        
		char* temp;
        m_strlen = strlen(str) + 1;
		temp = GET_SINGLETON_SCOPED(memory,MemoryManager)->AllocateNonPersistentString(m_strlen);
        strcpy_s(temp, m_strlen,static_cast<const char*>(str));
		m_str = temp;
    }
    NonPersistentString::~NonPersistentString()
    {

    }

    void NonPersistentString::Set(const char* str)
    {
		char* temp;
        m_strlen = strlen(str) + 1;
		temp = GET_SINGLETON_SCOPED(memory,MemoryManager)->AllocateNonPersistentString(m_strlen);
        strcpy_s(temp,m_strlen, str);
		m_str = temp;
    }
    const char* NonPersistentString::Get()const
    {
        return m_str;
    }
}