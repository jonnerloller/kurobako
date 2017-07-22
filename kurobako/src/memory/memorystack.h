#ifndef MEMORYSTACK_H
#define MEMORYSTACK_H
#include "types/sizedtypes.h"
#include "memorystats.h"
namespace kurobako::memory
{

    class MemoryStack
    {
        public:
            void* Allocate(uint64 size);

			void Deallocate(void* obj,uint64 size);
		
			void Reset();

			void Destroy();

			MemoryStack(uint64 size);
			MemoryStack(const MemoryStack& rhs) = delete;
			MemoryStack(MemoryStack&& rhs);
			MemoryStack& operator =(MemoryStack&& rhs);
            ~MemoryStack();

			const MemoryStats& GetStats() { return m_stats; }
			uint64 GetSize() { return m_size; }
        private:
            atomic_uintptr m_base;
            atomic_uintptr m_top;
			uint64 m_size;

			MemoryStats m_stats;
    };

	template <typename T>
	T* Allocate(MemoryStack& stack, uint64 num)
	{
		T* ret = static_cast<T*>(stack.Allocate(sizeof(T)));
		T* iter = ret;
		do
		{
			iter = new(iter) T();
			++iter;
		}(while --num != 0);
		return ret;
	}

	template <typename T>
	T* Allocate(MemoryStack& stack, const T& obj)
	{
		T* ret = static_cast<T*>(stack.Allocate(sizeof(T)));
		ret = new(ret) T(obj);
		return ret;
	}
}

#endif