#include"Threadpool.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

class Mytask
:public Task
{
public:
    void process()
    {
        ::srand(::time(nullptr));
        int num=rand()%100;
        cout<<"sub Thread"<<pthread_self()
            <<"Mytask: num="<<num<<endl;
        ::sleep(1);
    }

    ~Mytask()
    {
        cout<<"~Mytask()"<<endl;
    }
};

int main(void)
{
    unique_ptr<Task> task(new Mytask());
    Threadpool threadpool;
    threadpool.start();

    int i=20;
    while(i--)
    {
        threadpool.addTask(task.get());
        cout<<"main thread"<<pthread_self()
            <<"i= "<<i<<endl;
    }

    threadpool.stop();
    return 0;


}

