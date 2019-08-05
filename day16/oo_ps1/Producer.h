#pragma once
#include"Thread.h"

#include<iostream>

using std::endl;
using std::cout;


namespace wd{

class TaskQueue;

class Producer
:public Thread
{
public:
    Producer(TaskQueue &que)
    :_que(que){}
    ~Producer() {}

private:
    void run();

private:
    TaskQueue &_que;
};
}//end of namespace
