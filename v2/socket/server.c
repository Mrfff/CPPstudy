#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define ERR_EIXT(m) \
    do{\
    perror(m);\
    exit(EXIT_FAILURE);\
    }while(0)

#define MAXEVENTS 2048

int main(void)
{
    int listenfd=socket(PF_INET,SOCK_STREAM,0);//阻塞
    if(-1==listenfd)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    //服务器程序关闭后可以马上重启
    int on=1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
    {
        perror("setsockopt error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }
   
#if 0
    //一个服务器程序可以在同一台物理主机同一时刻启动
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on))<0)
    {
        perror("setsockopt error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }
#endif
    struct sockaddr_in addr;
    memset(&addr,0,sizeof addr);
    addr.sin_family =AF_INET;
    addr.sin_port=htons(2000);
    addr.sin_addr.s_addr=inet_addr("192.168.4.157");

    if(bind(listenfd,(struct sockaddr *)&addr,sizeof addr)==-1)
        ERR_EIXT("bind");


    if(listen(listenfd,SOMAXCONN))//最大连接数
        ERR_EIXT("listen");
    
    int efd=epoll_create1(0);
    if(-1==efd)
    {
        perror("epoll_create error");
        exit(EXIT_FAILURE);
    }

    struct epoll_event evt_listen;
    evt_listen.data.fd=listenfd;
    evt_listen.events=EPOLLIN;//(边缘触发)
    int ret=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&evt_listen);
    if(ret==-1)
    {
        perror("epoll_ctl add error");
        exit(EXIT_FAILURE);
    }

    struct epoll_event *events=(struct epoll_event *)calloc(MAXEVENTS,sizeof(struct epoll_event));
    while(1)
    {
        int i;
        int nready=epoll_wait(efd,events,MAXEVENTS,-1);
        for(i=0;i!=nready;++i)
        {
            int fd=events[i].data.fd;
            if(fd==listenfd)//新客户端连接
            {
                if(events[i].events&EPOLLIN)
                {
                    int peerfd=accept(fd,NULL,NULL);
                    if(-1==peerfd)
                    {
                        perror("accept error");
                        exit(EXIT_FAILURE);
                    }
                    //新的TCP连接
                    struct epoll_event ev;
                    ev.data.fd=peerfd;
                    ev.events=EPOLLIN;
                    ret=epoll_ctl(efd,EPOLL_CTL_ADD,peerfd,&ev);
                    if(-1==ret)
                    {
                        perror("epoll_ctl_add error");
                        exit(EXIT_FAILURE);
                    }
                }
                printf("client: -> server: has connected!\n");
                onConnection();//回调函数
            }
            else
            {
                if(events[i].events&EPOLLIN)
                {
                    char recvbuf[1024]={0};
                    int nread =read(fd,recvbuf,sizeof(recvbuf));
                    if(0==nread)//连接断开
                    {
                        struct epoll_event ev;
                        ev.data.fd=fd;
                        ret=epoll_ctl(efd,EPOLL_CTL_DEL,fd,&ev);
                        if(-1==ret)
                        {
                            perror("epoll_ctl_del error");
                            exit(EXIT_FAILURE);
                        }
                        close(fd);
                        printf("connection has closed!\n");
                        onClose();
                        continue;
                    }
                    onMessage();

                }
            }
        }
    }
    free(events);
    close(listenfd);
    return 0;

}

