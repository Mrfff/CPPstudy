#pragma once
#include"MutexLock.h"
#include"Condition.h"
#include"pthread.h"
    
#include<queue>
#include<iostream>
using std::queue;
using std::cout;
using std::endl;

namespace wd{

template<class T>
class TaskQueue
{
public:
    TaskQueue(size_t);
    bool empty()const;
    bool full()const;
    void push(T);
    T pop();


private:
    size_t _queSize;
    queue<T> _que;
    MutexLock _mutex;
    Condition _notfull;
    Condition _notempty;
        
};



}//end of namespace
#define FUCK
#include "TaskQueue.cc"//模版的实现在编译时应该放在一起
