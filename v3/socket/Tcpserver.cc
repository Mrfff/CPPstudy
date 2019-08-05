#include"Tcpserver.h"

namespace wd
{
Tcpserver::Tcpserver(const string &ip,unsigned short port)
:_acceptor(ip,port)
,_loop(_acceptor)
{}

void Tcpserver::start()
{
    _acceptor.ready();
    _loop.loop();
}
    
void Tcpserver::setConnectionCallback(TcpConnectionCallback &&cb)
{
    _loop.setConnectionCallback(std::move(cb));
}

void Tcpserver::setMessaageCallback(TcpConnectionCallback &&cb)
{
    _loop.setMessageCallback(std::move(cb));
}

void Tcpserver::setCloseCallback(TcpConnectionCallback &&cb)
{
    _loop.setCloseCallback(std::move(cb));
}
    


}//end of namespace



