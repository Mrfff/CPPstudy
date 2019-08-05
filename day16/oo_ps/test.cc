#include"TaskQueue.cc"
#include"Producer.cc"
#include"Consumer.cc"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
#include<memory>
using std::cout;
using std::endl;
using std::unique_ptr;
//using namespace wd;

int main()
{
    TaskQueue<int> taskque(10);
    cout<<"I get the task"<<endl;
    unique_ptr<Thread> producer(new Producer<int>(taskque));
    unique_ptr<Thread> consumer(new Consumer<int>(taskque));

    producer->start();
    consumer->start();


    producer->join();
    consumer->join();

return 0; 
}

