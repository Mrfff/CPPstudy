#include"Acceptor.h"
#include"TcpConnection.h"

#include<unistd.h>
#include<stdio.h>
#include<string.h>

#include<iostream>

using std::cout;
using std::endl;

int main(void)
{
    wd::Acceptor acceptor("192.168.4.157",2000);
    acceptor.ready();

    wd::TcpConnection conn(acceptor.accept());
    cout<<conn.toSting()<<" has connected "<<endl;
    conn.send("welcome to server~");
    printf("client data \n");
    cout<<conn.receive()<<endl;
    return 0;

}
