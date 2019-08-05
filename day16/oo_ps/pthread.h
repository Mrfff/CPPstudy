#pragma once
#include"Noncopyable.h"


#include<pthread.h>


namespace wd{

class Thread
:public Noncopyable
{
public:
    Thread()
    :_pthid(0)
    ,_isRunning(false)
    {}

    void start();
    void join();

    virtual ~Thread();

private:
    virtual void run()=0;
    static void *pthreadfunc(void *arg);

private:
    pthread_t _pthid;
    bool _isRunning;
};



}//end of wd

