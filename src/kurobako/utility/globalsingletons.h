#ifndef GLOBALSINGLETONS_H
#define GLOBALSINGLETONS_H

#define FOWARD_CLASS_DECLARATION(T) class T
#define DEFINE_SINGLETON(T) T* g_##T = nullptr
#define CREATE_SINGLETON(T) g_##T = kurobako::Singleton<T>::GetInstance()
#define SET_SINGLETON(T,Object) g_##T = Object
#define DECLARE_SINGLETON(T) extern T* g_##T
#define GET_SINGLETON(T) g_##T 

namespace kurobako
{
	namespace memory
	{
		FOWARD_CLASS_DECLARATION(MemoryManager);
		DECLARE_SINGLETON(MemoryManager);
	}
}

#endif