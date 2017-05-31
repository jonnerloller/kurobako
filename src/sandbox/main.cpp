#include <iostream>
#include "../kurobako/enginemain.h"
#include "../kurobako/memory/memorystack.h"
#include "../kurobako/memory/memorymanager.h"
#include "../kurobako/types/nonpersistentstring.h"
#include "../kurobako/log/logger.h"
#include "utility/singleton.h"
int main()
{
    kurobako::engine::InitEngine();
    std::cout << "Hello World!" << std::endl;

	constexpr uint64 allocation_size = 1 << 30;
	kurobako::memory::MemoryManager::InitializeMemoryManager(allocation_size);
	CREATE_SINGLETON_SCOPED(kurobako::log, Logger);
	
	for (int i = 0; i < 100; ++i)
	{
		//kurobako::NonPersistentString str = kurobako::NonPersistentString("Test String : %d", i);
		//std::cout << str.Get() << std::endl;
	}
	kurobako::NonPersistentString testStr = kurobako::NonPersistentString("This string has exactly %d characters", 38);
	kurobako::NonPersistentString testStr2 = kurobako::NonPersistentString("This string should fit");
	kurobako::NonPersistentString testStr3 = kurobako::NonPersistentString("But this should not");

	std::cout << testStr.Get() << std::endl;
	std::cout << testStr2.Get() << std::endl;
	std::cout << testStr3.Get() << std::endl;

	LOG_INFO(kurobako::NonPersistentString("Testing this feature!"), 5);
	DESTROY_SINGLETON_SCOPE(kurobako::log, Logger);
	kurobako::memory::MemoryManager::DestroyMemoryManager();
	//kurobako::memory::MemoryStack stack{10000};
	//
	//for (int i = 0; i < 100; ++i)
	//{
	//	int*p = (int*)stack.Allocate(sizeof(int) * 100);
	//	stack.Deallocate((void*)p,sizeof(int) * 100);
	//}

	//std::cout << "Total Allocations: " << stack.GetStats().m_numallocations << std::endl;
	//std::cout << "Current Num Allocations: " << stack.GetStats().m_numcurrentallocated << std::endl;
	//std::cout << "Total Deallocations: " << stack.GetStats().m_numdeallocations << std::endl;
	//std::cout << "Total Size Allocated: " << stack.GetStats().m_sizeallocated << std::endl;
	//std::cout << "Total Size Reserved: " << stack.GetSize() << std::endl;
}