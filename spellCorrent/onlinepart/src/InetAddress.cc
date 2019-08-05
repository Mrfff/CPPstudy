#include "../include/InetAddress.h"

#include<string.h>
namespace wd
{

InetAddress::InetAddress(unsigned short port)//本地端网络地址
{
    ::memset(&_addr,0,sizeof(struct sockaddr_in));
    _addr.sin_family=AF_INET;//大小端模式转换
    _addr.sin_port=htons(port);//主机字节序转换为网络字节序
    _addr.sin_addr.s_addr=INADDR_ANY;//inet_addr("0,0,0,0")代表本机地址（一个服务器可能有多个网卡）

}

InetAddress::InetAddress(const string &ip,unsigned short port)//对端网络地址
{
    ::memset(&_addr,0,sizeof(struct sockaddr_in));
    _addr.sin_family=AF_INET;//小端模式
    _addr.sin_port=htons(port);//htons主机转网络
    _addr.sin_addr.s_addr=inet_addr(ip.c_str());
}


InetAddress::InetAddress(const struct sockaddr_in&addr)
:_addr(addr)
{}

string InetAddress::ip()const
{
    return string(::inet_ntoa(_addr.sin_addr));//把ip地址转换为可以显示的地址
}

unsigned short InetAddress::port()const
{
    return ntohs(_addr.sin_port);//把端口号转换为可以打印的数字
}


}//end of namespace




