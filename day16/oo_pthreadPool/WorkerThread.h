#pragma once
#include"Thread.h"

namespace wd{

class Threadpool;

class WorkerThread
:public Thread
{
public:
    WorkerThread(Threadpool &Threadpool);
    ~WorkerThread();
    void run();

private:
    Threadpool &_threadpool;

};



}//end of namespace
