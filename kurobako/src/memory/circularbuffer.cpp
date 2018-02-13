#include "circularbuffer.h"
#include "memorystack.h"
namespace kurobako::memory
{
    circular_buffer::circular_buffer(stack& allocator, uint64 size)
    :   m_allocator(allocator),
        m_size(size),
        m_base(reinterpret_cast<uintptr>(allocator.allocate(size))),
        m_current(m_base.load()),
        m_destroyed(false)
    {

    }

	circular_buffer::~circular_buffer()
    {
        destroy();
    }

    void circular_buffer::destroy()
    {
        if(m_destroyed == false)
        {
			uintptr temp = m_base;
            m_allocator.deallocate(reinterpret_cast<void*>(temp),m_size);
        }
    }

    void* circular_buffer::allocate(uint64 size)
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

	void circular_buffer::reset()
	{
		m_current = m_base.load();
	}
}

