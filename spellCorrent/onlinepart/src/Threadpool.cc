#include"../include/Threadpool.h"

#include<unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd{


Threadpool::Threadpool(size_t threadNum,size_t queSize)
    :_threadNum(threadNum)
    ,_queSize(queSize)
    ,_taskque(queSize)
    ,_isExit(false)
{
    _threads.reserve(_threadNum);
}

Threadpool:: ~Threadpool()
{
    if(_isExit)
    {
        stop();
    }
}

void Threadpool::start()
{
    for(size_t i=0;i!=_threadNum;++i)
    {
        unique_ptr<Thread> thread(new Thread(std::bind(&Threadpool::threadfunc,this)));
        _threads.push_back(std::move(thread));
    }
    for(auto &thread:_threads)
    {
        thread->start();
    }
}

void Threadpool::stop()
{
    if(!_isExit)
    {
        while(!_taskque.empty())
        {
            ::sleep(1);
        }
        _isExit=true;
        _taskque.wakeup();
        for(auto &thread:_threads)
        {
            thread->join();
        }
    }
}

void Threadpool::addTask(Task &&task)
{
    _taskque.push(task);
}

Task Threadpool::getTask()
{
    return _taskque.pop();
}

void Threadpool::threadfunc()
{
    while(!_isExit)
    {
        Task task=getTask();
        if(task)
            task();//当任务执行过快，子线程会阻塞在getTask()方法上
    }
}

}//end of namespace
