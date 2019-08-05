#pragma once
#include"Tcpserver.h"
#include"Threadpool.h"
#include"Myconf.h"
namespace wd
{


class Spellserver
{
public:
    Spellserver(const string &cfgFileName);
    ~Spellserver() {}
    void onConnection(TcpConnectionPtr conn);
    void onMessage(TcpConnectionPtr conn);
    void onClose(TcpConnectionPtr conn);
    void start();


private:
    Tcpserver _tcpserver;
    Threadpool _threadpool;
    //Myconf &_conf;
};




}//end of wd
