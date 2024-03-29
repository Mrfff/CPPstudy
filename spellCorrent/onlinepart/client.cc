#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include <iostream>

using namespace std;
void do_service(int sockfd);


int main()
{
    int peerfd=socket(PF_INET,SOCK_STREAM,0);
    if(peerfd==-1)
    {
        perror("socket");
    }
    struct sockaddr_in addr;
    memset(&addr,0,sizeof addr);
    addr.sin_family =AF_INET;
    addr.sin_addr.s_addr=inet_addr("192.168.4.157");
    addr.sin_port =htons(2000);
    socklen_t len=sizeof addr;
    if(connect(peerfd,(struct sockaddr*)&addr,len)==-1)
    {
        perror("connect");
    }

    char buf[1024];
    memset(buf,0,sizeof(buf));
    read(peerfd,buf,sizeof(buf));
    printf("%s\n",buf);

    do_service(peerfd);


    return 0;
}

void do_service(int sockfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        fgets(sendbuf, sizeof sendbuf, stdin);
        cout << "发送：" << sendbuf;
        write(sockfd, sendbuf, strlen(sendbuf));
        int nread = read(sockfd, recvbuf, sizeof recvbuf);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            perror("read");
        }
        else if(nread == 0) 
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        printf("收到的消息 : %s\n", recvbuf);
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}






