#ifdef FUCK
#include"TaskQueue.h"

//#include <iostream>
using namespace wd;

template <class T>
TaskQueue<T>::TaskQueue(size_t queSize)
:_queSize(queSize)
,_mutex()
,_notfull(_mutex)
,_notempty(_mutex)
{}

template<class T>
bool TaskQueue<T>::empty()const
{
    return _que.size()==0;
}

template<class T>
bool TaskQueue<T>::full()const
{
    return _que.size()==_queSize;
}

template<class T>//生产者，不满就生产
 void TaskQueue<T>::push(T elem)
{
    AutoMutexLock autolock(_mutex);
    while(full())
    {
        _notfull.wait();
    }

    _que.push(elem);
    _notempty.notify();
}

template<class T>
T TaskQueue<T>::pop()//消费者，若不空就拿东西
{
    AutoMutexLock autolock(_mutex);
    while(empty())
    {
        _notempty.wait();
    }

    T value=_que.front();
    _que.pop();

    _notfull.notify();

    return value;
}
#endif
