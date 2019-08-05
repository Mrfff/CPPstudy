#pragma once
#include"Noncopyable.h"


#include<pthread.h>

#include<functional>
using std::function;
namespace wd{

class Thread
: Noncopyable
{
public:
    using ThreadCallback=function<void()>;
    Thread(ThreadCallback && cb)
    :_pthid(0)
    ,_isRunning(false)
    ,_cb(std::move(cb))
    {}

    void start();
    void join();

     ~Thread();

private:
    static void *pthreadfunc(void *arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
};



}//end of wd

