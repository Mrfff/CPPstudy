#pragma once
#include"pthread.h"
#include "TaskQueue.h"

namespace wd{

//class TaskQueue;

template<class T>
class Consumer
:public Thread
{
public:
    Consumer(TaskQueue<T> &que) 
    :_que(que)
    {}

    ~Consumer() {}
private:
     void run();


private:
    TaskQueue<T> &_que;
};


}
