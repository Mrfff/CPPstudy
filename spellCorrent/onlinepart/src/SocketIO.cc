#include"../include/SocketIO.h"

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>

namespace wd{

SocketIO::SocketIO(int fd)
:_fd(fd){}

int SocketIO::readn(char *buf,int len)
{
    int left=len;
    char *p=buf;
    while(left>0)
    {
        int ret=::read(_fd,p,left);
        if(ret==-1&&errno==EINTR)
        continue;
        else if(-1==ret)
        {
            perror("read");
            return len-left;
        }
        else
        {
            left-=ret;
            p+=ret;
        }
    }
    return len-left;
}

//读一行数据

int SocketIO::readline(char *buf,int maxlen)
{   
    int left=maxlen-1;
    char *p=buf;
    int ret;
    int total=0;
    while(left>0)
    {
        ret=recvPeek(p,left);//接收到数据的大小
        for(int i=0;i!=ret;++i)
        {
            if(p[i]=='\n')
            {
                //int sz=i+1;
                int sz=i + 1;
                readn(p,sz);
                total+=sz;
                p+=sz;
                *p='\0';
                return total;
            }
        }
        readn(p,ret);
        left-=ret;
        p+=ret;
        total+=ret;
    }
    //到最后也没发现\n
    *p='\0';
    return total;

}

int SocketIO::recvPeek(char *buf,int len)
{
    int ret;
    do
    {
     ret=::recv(_fd,buf,len,MSG_PEEK);
    }while(ret==-1&&errno==EINTR);
    return ret;

}

int SocketIO::writen(const char *buf,int len)
{
    int left=len;
    const char*p=buf;
    while(left>0)
    {
        int ret=::write(_fd,p,left);
        if(ret==-1&&errno==EINTR)
            continue;
        else if(ret==-1)
        {
            perror("write");
            return len-left;
        }
        else
        {
            left-=ret;
            p+=ret;
        }
    }
    return len-left;
}


}//end of namespace
