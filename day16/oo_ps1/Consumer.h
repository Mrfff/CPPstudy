#pragma once
#include"Thread.h"

namespace wd{

class TaskQueue;

class Consumer
:public Thread
{
public:
    Consumer(TaskQueue &que) 
    :_que(que)
    {}

private:
     void run();


private:
    TaskQueue &_que;
};


}
