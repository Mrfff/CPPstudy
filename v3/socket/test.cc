#include"Acceptor.h"
#include"TcpConnection.h"
#include"EventLoop.h"

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using std::cout;
using std::endl;

void onConnection(const wd::TcpConnectionPtr &conn)
{
    cout<<conn->toSting()<<" has connected! "<<endl;
    conn->send("welcome to server.");
}

void onMessage(const wd::TcpConnectionPtr &conn)
{
    string msg=conn->receive();
    cout<<">> receive mag from client: "<<msg<<endl;
    //业务逻辑交给decode,compute,encode
    conn->send(msg);
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    cout<<">> "<<conn->toSting()<<" has closed!"<<endl;
    
}


int main(void)
{
    wd::Acceptor acceptor("192.168.4.157",2000);
    acceptor.ready();

    wd::EventLoop loop(acceptor);
    loop.setConnectionCallback(onConnection);
    loop.setMessageCallback(onMessage);
    loop.setCloseCallback(onClose);

    loop.loop();
    return 0;

}

