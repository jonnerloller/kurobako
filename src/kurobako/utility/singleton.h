#ifndef SINGLETON_H
#define SINGLETON_H

namespace kurobako
{
    template <typename T>
    class Singleton
    {
        public:
			Singleton() :m_instance(nullptr) {}
		static  T& GetInstance() 
		{ 
			if (m_instance == nullptr)
			{
				void* ptr = kurobako::memory::MemoryManager::GetMemoryManager().AllocateSingleton(0, sizeof(T)); 
				m_instance = new(ptr) T;
			}
			return *m_instance;
		}
        static void SetInstance(T* instance){m_instance = instance;}
		static void DestroyInstance() { GET_SINGLETON_SCOPED(kurobako::memory, MemoryManager)->DeallocateSingleton(m_instance, sizeof(T)); }
        private:
	};
}

#endif