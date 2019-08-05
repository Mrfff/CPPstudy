#include"pthread.h"
#include"Noncopyable.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
#include<memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace wd;
class Myclass
:public Thread
{
    void run()
    {
        ::srand(::clock());
    int i=10;
    while(i--)
    {
        int num=::rand()%100;
        cout<<"pthread id= "<<pthread_self()
            <<": num= "<<num<<endl;
    }
    }

    ~Myclass(){cout<<"Myclass"<<endl;}
};

int main()
{
    unique_ptr<Thread> thread(new Myclass());
    thread->start();
    thread->join();

 
}

