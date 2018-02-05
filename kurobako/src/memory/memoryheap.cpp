#include "memoryheap.h"
#include "memoryconstants.h"
#include "memorystack.h"
#include <malloc.h>
#include <cstdlib>
#include <assert.h>
namespace kurobako::memory
{
    atomic_uint32 MemoryHeap::m_unique_allocation_sizes = 0;

	MemoryHeap::MemoryHeap(MemoryStack& allocator, uint64 size)
		: m_allocator(allocator),
		m_size(size),
		m_base(reinterpret_cast<uintptr>(allocator.Allocate(size))),
		m_top(m_base.load()),
		m_destroyed(false)
	{
        for (auto &i : m_heaplist)
        {
            i = 0;
        }
	}

    MemoryHeap::~MemoryHeap()
    {
		Destroy();
    }

	void MemoryHeap::Destroy()
	{
		if (m_destroyed == false)
		{
			uintptr temp = m_base;
			m_allocator.Deallocate(reinterpret_cast<void*>(temp), m_size);
		}
	}

    void* MemoryHeap::Allocate(uint64 size,uint32 heapid)
    {
#ifdef MEMORY_ALIGNMENT_ENABLED
		size = AlignSizeTo16(size);
#endif
        void* allocated_memory = nullptr;
		uintptr rep = 0;
		uintptr address_of_next_data = 0;
		bool success = false;
        // if we have something in the list, i.e not nullptr / 0
        do
        {
            uintptr rep = m_heaplist[heapid];

            // If ever rep is 0, we have no "available memory in the free-list, but we can grab more from the real heap"
			if (rep == 0)
			{
				success = false;
				break;
			}
			success = true;
				
            //m_heaplist[heapid]
            //MemoryHeader.m_top----->  MemoryHeader

            MemoryHeader* header = reinterpret_cast<MemoryHeader*>(rep);
			address_of_next_data = header->m_top.nextdata;
        
			// so now we basically want to swap.

			//well just now, when we checked, m_heaplist[heapid] was equal to rep! so it should stii be the same as rep!
			// and if its the same, let's swap it with address_of_next_data!
        }while(m_heaplist[heapid].compare_exchange_weak(rep,address_of_next_data));

		void* memory_from_free_list = reinterpret_cast<void*>(rep);
		void* memory_from_stack = nullptr;
        // if we reached here.. it means that there was nothing in the "free-list"
        if(success == false)
        {
			// We only add the wierd memory header thing if we care about mem tagging.
			uintptr offset = 0;
		#if defined(KBK_MEMTAG)
            offset = sizeof(MemoryHeader);
            #ifdef MEMORY_ALIGNMENT_ENABLED
                offset = AlignSizeTo16(offset);
            #endif
			size += offset;
        #endif
        #if defined(KBK_DEBUG) || defined(KBK_RELEASE)
			uintptr newtop = m_top + size;
			uintptr maxtop = m_base + m_size;
			assert(newtop < maxtop);
		#endif	
			m_stats.Allocate(size);
			uintptr temp = m_top.fetch_add(size);
			memory_from_stack = reinterpret_cast<void*>(temp + offset);
			// reminder in case i want to do something here...
			//#if defined(KBK_MEMTAG)
			//MemoryHeader* header = reinterpret_cast<MemoryHeader*>(temp);
			//#endif	
			return memory_from_stack;
        }

		// if we reached here, we just allocate the memory from the free_list, since we did not need to really allocate from our internal stack
        return memory_from_free_list;
    }

	void MemoryHeap::Deallocate(void* obj, uint32 heapid)
    {
		uint64 offset = 0;
		#if defined(KBK_MEMTAG)
		offset = sizeof(MemoryHeader);

        #ifdef MEMORY_ALIGNMENT_ENABLED
        offset = AlignSizeTo16(offset);
        #endif

		#endif	
		// This is relatively simple compared to ALLOC!
		// because..
		// simply put, we just need to push it into thje list. no need to check so many things
		// we do need to take into an offset if there is any.
		uintptr address_of_next_data = reinterpret_cast<uintptr>(obj)-offset;
		uintptr rep;
		do
		{
			rep = m_heaplist[heapid];
			// This is the header currently at the front of the list.
			// could be 0. But it doesn't matter.
			//In fact we don't even need this.
			//MemoryHeader* header = reinterpret_cast<MemoryHeader*>(rep);
			MemoryHeader* new_header = reinterpret_cast<MemoryHeader*>(address_of_next_data);
			new_header->m_top.nextdata = rep;			
		} while (!m_heaplist[heapid].compare_exchange_weak(rep, address_of_next_data));
    }
}