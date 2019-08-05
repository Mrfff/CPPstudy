#include"EventLoop.h"
#include"Acceptor.h"
#include"TcpConnection.h"

#include<assert.h>
#include<unistd.h>
#include<sys/eventfd.h>

#include<iostream>
using std::cout;
using std::endl;

namespace wd
{
EventLoop::EventLoop(Acceptor &acceptor)
:_efd(createEpollFd())
,_eventfd(createEventFd())
,_acceptor(acceptor)
,_eventList(1024)
,_isLooping(false)
{
    addEpollFdRead(_acceptor.fd());
    addEpollFdRead(_eventfd);
}

void EventLoop::runInloop(Functor&&cb)
{
    {
        AutoMutexLock autolock(_mutex);
        _pendingFunctors.push_back(std::move(cb));
    }
    wakeup();
}

void EventLoop::loop()
{
    _isLooping=true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    if(_isLooping)
        _isLooping=false;
}

void EventLoop::waitEpollFd()
{
    int nready;//n个事件已经准备好
    do
    {
        nready=epoll_wait(_efd,&*_eventList.begin(),_eventList.size(),5000);
    }while(nready==-1&&errno==EINTR);
    
    //事件未初始化成功
    if(nready==-1)
    {
        perror("epoll_wait");
        return;
    }
    
    //队列准备的时间超时
    else if(nready==0)
    {
        cout<<">> epoll_wait timeout! "<<endl;
    }
    
    //请求的序列过多需要扩大准备队列
    else
    {
        if(nready==static_cast<int>(_eventList.size()))
        {
            _eventList.resize(2*nready);
        }

        for(int i=0;i!=nready;++i)
        {
            int fd=_eventList[i].data.fd;//事件队列中的fd
            if(fd==_acceptor.fd())
            //处理新连接
            {
                if(_eventList[i].events&EPOLLIN)
                {
                    handleNewConnection();
                }
            }
            else if(fd==_eventfd)//处理数据
            {
                if(_eventList[i].events&EPOLLIN)
                {
                    handleRead();
                }

                doPendingFunctors();//发送数据

            }
            else//处理消息
            {
                if(_eventList[i].events&EPOLLIN)
                {
                    handleMessage(fd);
                }
            }

        }
    }

}

void EventLoop::handleNewConnection()
{
    int peerfd=_acceptor.accept();
    addEpollFdRead(peerfd);//添加新的文件描述符
    TcpConnectionPtr conn(new TcpConnection(peerfd,this));//建立新的连接
    conn->setConnectionCallback(_onConnection);//设置回调函数
    conn->setMessageCallback(_onMessage);
    conn->setCloseCallback(_onClose);

    _conns.insert(std::make_pair(peerfd,conn));
    conn->handleConnectionCallback();//执行连接回调

}

void EventLoop::handleMessage(int fd)
{
    bool isClosed=isConnectionClosed(fd);
    auto iter=_conns.find(fd);
    assert(iter!=_conns.end());//运行时断言(断言函数)
    
    if(!isClosed)
    {
        iter->second->handleMessageCallback();
    }else
    {
        delEpollFdRead(fd);
        iter->second->handleCloseCallback();
        _conns.erase(iter);
    }

}

void EventLoop::handleRead()
{
    uint64_t howmany;
    int ret =::read(_eventfd,&howmany,sizeof(howmany));
    if(ret!=sizeof(howmany))
    {
        perror("read");
    }
}

void EventLoop::wakeup()
{
    u_int64_t one=1;
    int ret=::write(_eventfd,&one,sizeof(one));
    if(-1==ret)
    {
        perror("write");
    }
}

void EventLoop::doPendingFunctors()
{
    vector<Functor> tmp;
    {
        AutoMutexLock autolock(_mutex);
        tmp.swap(_pendingFunctors);
    }

    for(auto &functor:tmp)
    {
        functor();
    }
}

bool EventLoop::isConnectionClosed(int fd)
{
    int ret;
    do{
        char buf[1024]={0};
        ret=recv(fd,buf,sizeof(buf),MSG_PEEK);
    }while(ret==-1&&errno ==EINTR);

    return (ret==0);
}

int EventLoop::createEpollFd()
{
    int ret=::epoll_create1(0);
    if(ret==-1)
    {
        perror("epoll_create1");
    }
    return ret;
}

int EventLoop::createEventFd()
{
    int ret=::eventfd(0,0);
    if(-1==ret)
    {
        perror("eventfd");
    }
    return ret;
}

void EventLoop::addEpollFdRead(int fd)
{
    struct epoll_event evt;
    evt.data.fd=fd;
    evt.events=EPOLLIN;
    int ret= epoll_ctl(_efd,EPOLL_CTL_ADD,fd,&evt);
    if(-1==ret)
    {
        perror("epoll_ctl");
    }

}

void EventLoop::delEpollFdRead(int fd)
{
    struct epoll_event evt;
    evt.data.fd=fd;
    int ret=epoll_ctl(_efd,EPOLL_CTL_DEL,fd,&evt);
    if(-1==ret)
    {
        perror("epoll_ctl");
    }


}



}//end of namespace
