#ifndef _WD_TCPCONNECTION_H__
#define _WD_TCPCONNECTION_H__

#include"Socket.h"
#include"SocketIO.h"
#include"InetAddress.h"
#include"Noncopyable.h"

#include<string>
using std::string;

namespace wd{
class TcpConnection
{
public:
    TcpConnection(int fd);
    ~TcpConnection();

    string receive();
    void send(const string &msg);

    string toSting() const;
    void shutdown();
private:
    InetAddress getLocalAddr(int fd);
    InetAddress getPeerAddr(int fd);
private:
    Socket _sock;
    SocketIO _sockIo;
    InetAddress _locaAddr;//本地地址
    InetAddress _peerAddr;//对端地址
    bool _isShutdownWrite;
};


}//end of namespace
#endif
