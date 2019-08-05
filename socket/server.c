#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void)
{
    int listenfd=socket(AF_INET,SOCK_STREAM,0);//阻塞
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
    
    //一个服务器程序可以在同一台物理主机同一时刻启动
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on))<0)
    {
        perror("setsockopt error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    printf("sizeof(struct sockaddr_in) = %ld \n",sizeof(struct sockaddr_in));
    serverAddr.sin_family =AF_INET;
    serverAddr.sin_port=htons(2000);
    serverAddr.sin_addr.s_addr=INADDR_ANY;

    int ret=bind(listenfd,
                 (struct sockaddr *)&serverAddr,
                 sizeof(struct sockaddr));

    if(-1==ret)
    {
        perror("bind");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    ret =listen(listenfd,10);//最大连接数
    if(-1==ret)
    {
        perror("listen");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        int peerFd=accept(listenfd,NULL,NULL);
        char buf[1024]="welcome wo servers.";
        ret=write(peerFd,buf,strlen(buf));

        memset(buf,0,1024);
        printf("client data:\n");
        ret=read(peerFd,buf,1024);
        printf("%s\n",buf);

    }
    close(listenfd);
    return 0;

}

