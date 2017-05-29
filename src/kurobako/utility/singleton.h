#ifndef SINGLETON_H
#define SINGLETON_H

namespace kurobako
{
    template <typename T>
    class Singleton
    {
        public:
        static T& GetInstance(){return *m_instance;}
        static const  T& GetInstance(return *m_instance;)
        static void CreateInstance(){}
        static void DestroyInstance(){}
        static void RegisterGlobalInstance(T* & reg){reg = m_instance;};
        private:
        static T* m_instance;
    }
}

#endif