#include <iostream>
#include "kurobako/src/enginemain.h"
#include "kurobako/src/memory/memorystack.h"
#include "kurobako/src/memory/memorymanager.h"
#include "kurobako/src/types/nonpersistentstring.h"
#include "kurobako/src/log/logger.h"
#include "kurobako/src/types/sizedtypes.h"
#include "kurobako/src/utility/singleton.h"
#include "kurobako/src/tests/tests.h"
int main()
{
    kurobako::engine::InitEngine();
	kurobako::tests::RunUnitTests();
}