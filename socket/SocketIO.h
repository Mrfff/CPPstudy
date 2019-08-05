#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__


namespace wd
{
class SocketIO
{
public:
    explicit
    SocketIO(int fd);

    int readn(char *buf,int len);
    int readline(char *buf,int maxlen);
    int writen(const char *buf,int len);

private:
    int recvPeek(char *buf,int len);

private:
    int _fd;
};


}//end of namespace
#endif
