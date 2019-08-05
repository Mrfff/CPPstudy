#pragma once
#include"pthread.h"
#include"TaskQueue.h"

#include<iostream>

using std::endl;
using std::cout;
using namespace wd;

//class TaskQueue;

template<class T>
class Producer
:public Thread
{
public:
    Producer(TaskQueue<T> &que)
    :_que(que){}
    ~Producer() {}

private:
    void run();

private:
    TaskQueue<T> &_que;
};

