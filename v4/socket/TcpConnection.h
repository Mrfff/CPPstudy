#ifndef _WD_TCPCONNECTION_H__
#define _WD_TCPCONNECTION_H__

#include"Socket.h"
#include"SocketIO.h"
#include"InetAddress.h"
#include"Noncopyable.h"

#include<string>
#include<memory>
#include<functional>
using std::function;
using std::string;

namespace wd{

class TcpConnection;
using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
using TcpConnectionCallback=function<void (const TcpConnectionPtr&)>;

class EventLoop;

class TcpConnection
:Noncopyable
,public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd,EventLoop *);
    ~TcpConnection();

    string receive();
    void send(const string &msg);
    void sendInloop(const string &msg);

    string toSting() const;
    void shutdown();

    void setConnectionCallback(const TcpConnectionCallback &cb);
    void setMessageCallback(const TcpConnectionCallback &cb);
    void setCloseCallback(const TcpConnectionCallback &cb);

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
private:
    InetAddress getLocalAddr(int fd);
    InetAddress getPeerAddr(int fd);
private:
    Socket _sock;
    SocketIO _sockIo;
    InetAddress _locaAddr;//本地地址
    InetAddress _peerAddr;//对端地址
    bool _isShutdownWrite;
    EventLoop *_loop;//计算线程的获取

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;

};


}//end of namespace
#endif
