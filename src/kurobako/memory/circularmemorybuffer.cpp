#include "circularmemorybuffer.h"
#include "memorystack.h"
namespace kurobako::memory
{
    CircularMemoryBuffer::CircularMemoryBuffer(MemoryStack& allocator, uint64 size)
    :   m_allocator(allocator),
        m_size(size),
        m_base(reinterpret_cast<uintptr>(allocator.Allocate(size))),
        m_current(m_base.load()),
        m_destroyed(false)
    {

    }

	CircularMemoryBuffer::~CircularMemoryBuffer()
    {
        Destroy();
    }

    void CircularMemoryBuffer::Destroy()
    {
        if(m_destroyed == false)
        {
			uintptr temp = m_base;
            m_allocator.Deallocate(reinterpret_cast<void*>(temp),m_size);
        }
    }

    void* CircularMemoryBuffer::Allocate(uint64 size)
    {
		uintptr current;
		uintptr target;
        do
        {
            current = m_current;
            target = (current + size - m_base >= m_size)?m_base+size:current+size;
        }while(!m_current.compare_exchange_weak(current,target));
        return reinterpret_cast<void*>(target - size);
    }

	void CircularMemoryBuffer::Reset()
	{
		m_current = m_base.load();
	}
}

