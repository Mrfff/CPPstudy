#pragma once
#include<iostream>
#include<functional>
using std::endl;
using std::cout;
using std::function;

namespace wd
{
class Timefd
{

public:

    using TimeCallback=function<void()>;
    Timefd(int ,int ,TimeCallback&&);
    void start();
    void stop();
private:
    int createTimefd();
    void setTimefd(int ,int);
    void handleRead();
private:
    int _fd;
    int _initialTime;
    int _intervalTime;
    TimeCallback _cb;
    bool _isStarted;
};



}//end of namespace
