#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__
#include"Acceptor.h"
#include"EventLoop.h"
#include"TcpConnection.h"

namespace wd{

using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
using TcpConnectionCallback=std::function<void(const TcpConnectionPtr&)>;

class Tcpserver
{
public:
    Tcpserver(const string &ip,unsigned short port);
    void start();

    void setConnectionCallback(TcpConnectionCallback &&cb);
    void setMessaageCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);

private:
    Acceptor _acceptor;
    EventLoop _loop;

};




}//end of namespace
#endif

