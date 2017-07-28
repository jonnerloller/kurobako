#ifndef GLOBALSINGLETONS_H
#define GLOBALSINGLETONS_H

#define FOWARD_CLASS_DECLARATION(T) class T
#define DEFINE_SINGLETON(T) T* g_##T = nullptr
#define CREATE_SINGLETON(T,...) do{void* ptr = kurobako::memory::MemoryManager::GetMemoryManager().AllocateSingleton(0,sizeof(T));g_##T = new(ptr) T(__VA_ARGS__);}while(0)
#define CREATE_SINGLETON_SCOPED(scope,T,...) do{void* ptr = kurobako::memory::MemoryManager::GetMemoryManager().AllocateSingleton(0,sizeof(scope::T));scope::g_##T = new(ptr) scope::T(__VA_ARGS__);}while(0)
#define DESTROY_SINGLETON_SCOPE(scope,T) do{void* ptr = scope::g_##T; kurobako::memory::MemoryManager::GetMemoryManager().DeallocateSingleton(ptr,sizeof(scope::T));}while(0)
#define DESTROY_SINGLETON_(T) do{void* ptr = g_##T; kurobako::memory::MemoryManager::GetMemoryManager().DeallocateSingleton(ptr,sizeof(T));}while(0)
#define SET_SINGLETON(T,Object) g_##T = Object
#define DECLARE_SINGLETON(T) extern T* g_##T
#define GET_SINGLETON(T) g_##T 
#define GET_SINGLETON_SCOPED(Scope,T) Scope::g_##T 

namespace kurobako
{
	namespace memory
	{
		FOWARD_CLASS_DECLARATION(MemoryManager);
		DECLARE_SINGLETON(MemoryManager);
	}
	namespace log 
	{
		FOWARD_CLASS_DECLARATION(Logger);
		DECLARE_SINGLETON(Logger);
	}
}

#endif