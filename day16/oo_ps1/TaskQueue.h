#pragma once
#include"MutexLock.h"
#include"Condition.h"
    
#include<queue>
using std::queue;

namespace wd{

class TaskQueue
{
public:
    TaskQueue(size_t);
    
    bool empty()const;
    bool full()const;
    void push(int );
    int pop();


private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notfull;
    Condition _notempty;
        
};


}//end of namespace
