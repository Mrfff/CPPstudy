#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include"InetAddress.h"
#include"Socket.h"

namespace wd{

class Acceptor
{
public:
    Acceptor(unsigned short port);//端口号
    Acceptor(const string &ip,unsigned short port);

    void ready();
    
    int fd()const {return _listensock.fd();}
    int accept();

private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();//绑定端口号
    void listen();//监听

private:
    InetAddress _addr;//网络地址号
    Socket _listensock;//监听的文件描述符

};

}//end of namespace
#endif
