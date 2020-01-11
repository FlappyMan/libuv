#ifndef _BLOCKQUEUE_H_
#define _BLOCKQUEUE_H_
#include "uv.h"
#include <queue>

template <typename T>
class UBBlockQueue
{
    public:
        UBBlockQueue();
        ~UBBlockQueue();
        T* get();
        void put(T* data);
        size_t size();
        void put(std::vector<T*> &vec);
        void get(std::vector<T*> &vec,int iSize);
    private:
        std::queue<T*> m_queue;
        uv_mutex_t m_mutex;
};

template <typename T>
UBBlockQueue<T>::UBBlockQueue()
{
    uv_mutex_init(&m_mutex);
}

template <typename T>
UBBlockQueue<T>::~UBBlockQueue() {
    uv_mutex_destroy(&m_mutex);
}

template <typename T>
T* UBBlockQueue<T>::get()
{
    uv_mutex_lock(&m_mutex);
    if (m_queue.empty())
    {
        uv_mutex_unlock(&m_mutex);
        return NULL;
    }
    T* data = m_queue.front();
    m_queue.pop();
    uv_mutex_unlock(&m_mutex);
    return data;
}

template <typename T>
void UBBlockQueue<T>::put(T* data)
{
    uv_mutex_lock(&m_mutex);
    if (m_queue.size() > 1000000)
    {
        usleep(100*1000);
    }   
    m_queue.push(data);
    uv_mutex_unlock(&m_mutex);
}
template <typename T>
void UBBlockQueue<T>::put(std::vector<T*> &vec)
{
    uv_mutex_lock(&m_mutex);
    if (m_queue.size() > 1000000)
    {
        assert(m_queue.size() < 1000000);
        usleep(100*1000);
    }
    int iVecSize = vec.size();
    for (int iIndex = 0; iIndex < iVecSize; iIndex++)
    {
        m_queue.push(vec[iIndex]);
    }
    
    uv_mutex_unlock(&m_mutex);
}

template <typename T>
void UBBlockQueue<T>::get(std::vector<T*> &vec,int iSize)
{
    uv_mutex_lock(&m_mutex);
    if (m_queue.empty())
    {
        assert(!m_queue.empty());
        uv_mutex_unlock(&m_mutex);
        return;
    }
    for (int i = 0; i < iSize; i++)
    {
        T* data = m_queue.front();
        m_queue.pop();
        vec.push_back(data);
    }
    uv_mutex_unlock(&m_mutex);
}


template<typename T>
size_t UBBlockQueue<T>::size()
{
    size_t size = 0;
    uv_mutex_lock(&m_mutex);
    size = m_queue.size();
    uv_mutex_unlock(&m_mutex);
    return size;
}
#endif
