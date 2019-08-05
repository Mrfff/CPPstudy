#include"pthread.h"

#include <iostream>

namespace wd{

void Thread::start()
{
    pthread_create(&_pthid,nullptr,pthreadfunc,this);
    _isRunning=true;
} 

void *Thread::pthreadfunc(void *arg)
{
    Thread *pthread=(Thread*)(arg);
    if(pthread)
    {
        pthread->_cb();
    }

    return nullptr;    
}

void Thread::join()
{
    if(_isRunning)
    {
        pthread_join(_pthid,nullptr);
    }
}
 Thread::~Thread()
{
    std::cout<<"~Thread"<<std::endl;
}


}//end of namespace
