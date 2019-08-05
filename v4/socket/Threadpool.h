#pragma once

#include"TaskQueue.h"
#include"Thread.h"


#include<vector>
#include<memory>

using std::vector;
using std::unique_ptr;

namespace wd{

using Task=std::function<void()>;

class Threadpool
{
public:
    Threadpool(size_t ,size_t );
    ~Threadpool();
    
    void start();
    void addTask(Task &&task);

    void stop();
private:
    Task getTask();
    void threadfunc();

private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskque;
    bool _isExit;

};


}//end of namespace
