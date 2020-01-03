#ifndef _BLOCKQUEUE_H_
#define _BLOCKQUEUE_H_
#include "UProtocol.h"
#include <queue>

template <typename T>
class BlockQueue
{
    public:
        BlockQueue();
        ~BlockQueue();
        T get();
        void put(T data);
        size_t size();
    private:
        std::queue<T> m_queue;
        uv_mutex_t m_mutex;
        uv_cond_t m_getCondition;
};

template <typename T>
BlockQueue<T>::BlockQueue()
{
    uv_mutex_init(&m_mutex);
    uv_cond_init(&m_getCondition);
}

template <typename T>
BlockQueue<T>::~BlockQueue() {
    uv_mutex_destroy(&m_mutex);
    uv_cond_destroy(&m_getCondition);
}

template <typename T>
T BlockQueue<T>::get()
{
    uv_mutex_lock(&m_mutex);
    if (m_queue.empty())
    {
        uv_cond_wait(&m_getCondition, &m_mutex);
    }
    T data = m_queue.front();
    m_queue.pop();
    uv_mutex_unlock(&m_mutex);
    return data;
}

template <typename T>
void BlockQueue<T>::put(T data)
{
    uv_mutex_lock(&m_mutex);
    m_queue.push(data);
    uv_cond_signal(&m_getCondition);
    uv_mutex_unlock(&m_mutex);
}

template<typename T>
size_t BlockQueue<T>::size()
{
    size_t size = 0;
    uv_mutex_lock(&m_mutex);
    size = m_queue.size();
    uv_mutex_unlock(&m_mutex);
    return size;
}
#endif
