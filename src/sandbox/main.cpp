#include <iostream>
#include "../kurobako/enginemain.h"
#include "../kurobako/memory/memorystack.h"
int main()
{
    kurobako::engine::InitEngine();
    std::cout << "Hello World!" << std::endl;
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