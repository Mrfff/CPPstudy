#include "../include/timefd.h"
#include<sys/timerfd.h>
#include<unistd.h>
#include<poll.h>

namespace wd
{
Timefd::Timefd(int initialTime,int intervalTime,TimeCallback &&cb)
:_fd(createTimefd())
,_initialTime(initialTime)
,_intervalTime(intervalTime)
,_cb(std::move(cb))
,_isStarted(false)
{}

void Timefd::start()
{
    _isStarted=true;
    struct pollfd pfd;
    pfd.fd=_fd;
    pfd.events=POLLIN;
    
    setTimefd(_initialTime,_intervalTime);

    while(_isStarted)
    {
        int nready=::poll(&pfd,1,5000);
        if(-1==nready&&errno==EINTR){continue;}
        else if (-1==nready){return;}
        else if(0==nready){printf(">> poll time out");}
        else 
        {
            if(pfd.revents&POLLIN)//poll返回写入revents，他是整形用的是某一位表示，应该用与操作
            {
                handleRead();
                if(_cb)
                _cb();
            }
        }
    }
}

void Timefd::setTimefd(int initialTime,int intervalTime)
{
    struct itimerspec value;
    value.it_value.tv_sec=initialTime;
    value.it_value.tv_nsec=0;
    value.it_interval.tv_sec=intervalTime;
    value.it_interval.tv_nsec=0;

    int ret=::timerfd_settime(_fd,0,&value,nullptr);
    if(-1==ret)
    {
        perror("timerfd_settime");
    }
}

void Timefd::handleRead()//处理读操作
{
    uint64_t howmany;//超时重传的次数；
    int ret=read(_fd,&howmany,sizeof(uint64_t));
    if(sizeof(howmany)!=ret)
    {
        perror("read");
    }


}

void Timefd::stop()
{
    if(_isStarted)
    {
        _isStarted=false;
        setTimefd(0,0);
    }
    
}

int Timefd::createTimefd()
{
    int fd=::timerfd_create(CLOCK_REALTIME,0);
    if(-1==fd)
    {
        perror("timerfd_create");
    }
    return fd;
}

}//end of namespace
