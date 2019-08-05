#pragma once
#include"Noncopyable.h"


#include<pthread.h>
#include<functional>

namespace wd{

class Thread
: Noncopyable
{
public:
    using ThreadCallback=std::function<void()>;
    Thread(ThreadCallback &&cb)
    :_pthid(0)
    ,_cb(std::move(cb))
    ,_isRunning(false)
    {}

    void start();
    void join();

    virtual ~Thread();

private:
    static void *pthreadfunc(void *arg);

private:
    pthread_t _pthid;
    ThreadCallback _cb;
    bool _isRunning;
};



}//end of wd

