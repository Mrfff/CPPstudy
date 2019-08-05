#pragma once
#include"Thread.h"
#include"timefd.h"
#include<iostream>

using std::endl;
using std::cout;

namespace wd
{
class timeThread
{
    using TimeCallback=function<void()>;
public:
    timeThread(int initialTime,int intervakTime ,TimeCallback &&cb)
    :_timer(initialTime,intervakTime,std::move(cb))
    ,_thread(std::bind(&Timefd::start,&_timer))
    {}

    void start()
    {
        _thread.start();
    }

    void stop()
    {
        _timer.stop();
        _thread.join();
    }
private:
    Timefd _timer;
    Thread _thread;
};






}//end of namespace
