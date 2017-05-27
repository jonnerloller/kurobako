#include "enginemain.h"
#include "kurobakoconfig.h"
#include <iostream>
namespace kurobako::engine
{
    void InitEngine()
    {
		int i = 0;
		i = 3;
		++i;

		int*p = nullptr;
#if defined(KUROBAKODEBUG)
		*p = 3;
        std::cout << "Initializing Engine(Debug)" << std::endl;
#elif defined(KUROBAKORELEASE)
		std::cout << "Initializing Engine(Release)" << std::endl;
#elif defined(KUROBAKOPROFILE)
		std::cout << "Initializing Engine(Profile)" << std::endl;
#elif defined(KUROBAKOFINAL)
		std::cout << "Initializing Engine(Final)" << std::endl;
#endif
    }
}