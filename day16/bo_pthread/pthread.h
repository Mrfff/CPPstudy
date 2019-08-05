#pragma once
#include"Noncopyable.h"


#include<pthread.h>

#include<functional>
using std::function;
namespace wd{

class Thread
:public Noncopyable
{
public:
    using ThreadCallBack= function<void()>;
    
    Thread(ThreadCallBack &&cb)
    :_pthid(0)
    ,_isRunning(false)
    ,_cb(std::move(cb))
    {}

    void start();
    void join();
    void process();
    virtual ~Thread();

private:
    //virtual void run()=0;
    static void *pthreadfunc(void *arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallBack _cb;
};



}//end of wd

