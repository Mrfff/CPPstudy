#include"WorkerThread.h"
#include"Threadpool.h"

#include<iostream>
using std::endl;
using std::cout;

namespace wd{


WorkerThread::WorkerThread(Threadpool &threadpool)
:_threadpool(threadpool)
{
    cout<<"WorkerThread()"<<endl;
}

WorkerThread::~WorkerThread()
{
    cout<<"~WorkerThread()"<<endl;
}

void WorkerThread::run()
{
    _threadpool.threadfunc();
}


}//end of namespace
