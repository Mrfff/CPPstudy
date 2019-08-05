#include"TcpConnection.h"
#include"InetAddress.h"

#include<error.h>
#include<stdlib.h>
#include<sys/socket.h>

#include<sstream>

namespace wd
{

TcpConnection::TcpConnection(int fd)
:_sock(fd)
,_sockIo(fd)
,_locaAddr(getLocalAddr(fd))
,_peerAddr(getPeerAddr(fd))
,_isShutdownWrite(false)
{}

TcpConnection::~TcpConnection()
{
    if(!_isShutdownWrite)
    {
        shutdown();
    }
}

string TcpConnection::receive()
{
    char buf[65536]={0};
    _sockIo.readline(buf,sizeof(buf));
    return string(buf);
}

void TcpConnection::send(const string &msg)
{
    _sockIo.writen(msg.c_str(),msg.size());
}

void TcpConnection::shutdown()
{
    if(!_isShutdownWrite)
    {
        _isShutdownWrite=true;
        _sock.shutdownWrite();
    }
}

string TcpConnection::toSting()const
{
    std::ostringstream oss;
    oss<<_locaAddr.ip()<<":"<<_locaAddr.port()<<"---->"
        <<_peerAddr.ip()<<":"<<_peerAddr.port();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr(int fd)
{
    struct sockaddr_in addr;
    socklen_t len=sizeof(struct sockaddr);
    if(getsockname(_sock.fd(),(struct sockaddr*)&addr,&len)==-1)
    {
        perror("getsockname");
    }
    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr(int fd)
{
    struct sockaddr_in addr;
    socklen_t len=sizeof(struct sockaddr);
    if(getpeername(_sock.fd(),(struct sockaddr*)&addr,&len)==-1)
    {
        perror("getpeername");
    }
    return InetAddress(addr);
}


}//end of namespace
