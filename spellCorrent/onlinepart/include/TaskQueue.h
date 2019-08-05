#pragma once
#include"MutexLock.h"
#include"Condition.h"

#include<queue>
#include<functional>
using std::queue;

namespace wd{

using Task=std::function<void()>;
using ElemType=Task ;

class TaskQueue
{
public:
    TaskQueue(size_t);
    
    bool empty()const;
    bool full()const;
    void push(ElemType elem);
    ElemType pop();

    void wakeup();

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notfull;
    Condition _notempty;
    bool _flag;
};


}//end of namespace
