#include"timefd.h"
#include"Thread.h"

#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#include<iostream>
using std::endl;
using std::cout;

void getNumber()
{
    ::srand(::time(nullptr));
    int num=::rand()%100;
    cout<<"timefd get num = "<<num<<endl;
}
int main(void)
{
    wd::Timefd timer(3,6,getNumber);
    wd::Thread thd(std::bind(&wd::Timefd::start,&timer));
    thd.start();
    cout<<"main thread"<<endl;
    ::sleep(10);
    timer.stop();
    thd.join();
    return 0;
}







