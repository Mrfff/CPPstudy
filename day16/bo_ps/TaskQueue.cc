#include"TaskQueue.h"

//#include <iostream>

namespace wd{

TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_mutex()
,_notfull(_mutex)
,_notempty(_mutex)
{}

bool TaskQueue::empty()const
{
    return _que.size()==0;
}

bool TaskQueue::full()const
{
    return _que.size()==_queSize;
}

 void TaskQueue::push(int elem)
{
    AutoMutexLock autolock(_mutex);
    while(full())
    {
        _notfull.wait();
    }

    _que.push(elem);
    _notempty.notify();
}

int TaskQueue::pop()//消费者，若不空就拿东西
{
    AutoMutexLock autolock(_mutex);
    while(empty())
    {
        _notempty.wait();
    }

    int value=_que.front();
    _que.pop();

    _notfull.notify();

    return value;
}


}//end of namespace
