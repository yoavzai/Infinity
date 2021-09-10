#include "thread.hpp"

namespace ilrd
{

template<typename T>
class Singleton
{
public:
    static T* Instance();

private:
    static T* m_instance;
    static pthread_mutex_t m_mutex;

    Singleton();
};

template<typename T>
T* Singleton<T>::m_instance = NULL;

template<typename T>
pthread_mutex_t Singleton<T>::m_mutex;

template<typename T>
T* Singleton<T>::Instance()
{
    if (m_instance == NULL)
    {
        pthread_mutex_lock(&m_mutex);

        if (m_instance == NULL)
        {
            m_instance = new T;
        }

        pthread_mutex_unlock(&m_mutex);
    }

    return m_instance;
}

} // namespace ILRD