#ifndef NONPERSISTENTSTRING_H
#define NONPERSISTENTSTRING_H
#include "sizedtypes.h"
namespace kurobako
{
    class NonPersistentString
    {
        enum
        {
            MAX_STRING_SIZE = 1 << 10
        };
        public:
        //NonPersistentString(const char* str);
        NonPersistentString(const char* format,...);

        // We are ok doing a shallow copy. since this is basically a global string buffer
        NonPersistentString(NonPersistentString& rhs) = default;
        NonPersistentString& operator = (NonPersistentString& rhs) = default;
        ~NonPersistentString();

        void Set(const char* str);
        const char* Get()const;

		inline uint64 GetLength() const { return m_strlen; }
        private:
        const char* m_str;
        uint64 m_strlen;
    };
}

#endif