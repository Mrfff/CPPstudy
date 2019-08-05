#include"Threadpool.h"
#include"Tcpserver.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace wd;

wd::Threadpool *gThreadpool =nullptr;

class Mytask
{
public:
    Mytask(const string &msg,const TcpConnectionPtr&conn)
    :_msg(msg)
    ,_conn(conn){}
    
    void process()
    {
        ::srand(::time(nullptr));
        int num=rand()%100;
        cout<<"sub Thread"<<pthread_self()
            <<"Mytask: num="<<num<<endl;
        ::sleep(1);
    }

    ~Mytask()
    {
        cout<<"~Mytask()"<<endl;
    }
private:
    string _msg;
    TcpConnectionPtr _conn;
};

void onConnection(const TcpConnectionPtr &conn)
{
    cout<<conn->toSting()<<"has connected! "<<endl;
    conn->send("welcome to server.");
}

void onMessage(const TcpConnectionPtr&conn)
{
    cout<<"onMessage... "<<endl;
    string msg=conn->receive();
    cout<<">> receive msg from client: "<<msg<<endl;
    Mytask task(msg,conn);
    gThreadpool->addTask(std::bind(&Mytask::process,task));
}

void onClose(const TcpConnectionPtr &conn)
{
    cout<<"onClose.... "<<endl;
    cout<<conn->toSting()<<"has closed! "<<endl;
}

#if 0
class EchoServer
{
public:
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn);
    void onClose(const TcpConnectionPtr &conn);

    void process();

private:
    Threadpool _threadpool;
    Tcpserver _server;
};
#endif


int main(void)
{
    Threadpool threadpool(4,10);
    threadpool.start();
    
    gThreadpool =&threadpool;
    Tcpserver server("192.168.4.157",2000);
    server.setCloseCallback(onClose);
    server.setConnectionCallback(onConnection);
    server.setMessaageCallback(onMessage);
    server.start();
    return 0;


}

