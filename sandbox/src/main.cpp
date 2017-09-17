#include <iostream>
#include "kurobako/src/enginemain.h"
#include "kurobako/src/memory/memorystack.h"
#include "kurobako/src/memory/memorymanager.h"
#include "kurobako/src/types/nonpersistentstring.h"
#include "kurobako/src/log/logger.h"
#include "kurobako/src/types/sizedtypes.h"
#include "kurobako/src/utility/singleton.h"
#include "kurobako/src/tests/tests.h"

#include "kurobako\src\graphics\vk\instance.h"

int main()
{
  auto layers = sandcastle::graphics::enumerate_instance_layers();

  for (const auto& elem : layers) {
    std::cout << elem.layerName << " " << elem.description << std::endl;
  }

  kurobako::engine::InitEngine();
  kurobako::tests::RunUnitTests();
  kurobako::engine::RunEngine();


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
