#include"TaskQueue.h"
#include"Thread.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
#include<memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace wd;

class Producer
{
public:
    void producer(TaskQueue &que)
    {
        ::srand(::time(nullptr));
        int i=10;
        while(i--)
        {
            int num=::rand()%100;
            que.push(num);
            cout << "producer thread " << pthread_self()
                << ": produce a number = " << num << endl;
        }
    }
};

class Consumer
{
public:
    void consumer(TaskQueue &que)
    {
        int i=10;
        while(i--)
        {
            int num=que.pop();
            cout << "consumer thread " << pthread_self() <<
                  ":  consume a number = " << num << endl;
        }

    }
};

int main()
{
    TaskQueue taskque(10);
    unique_ptr<Thread> producer1(new Thread(std::bind(&Producer::producer
                                            ,Producer(),std::ref(taskque))));//ref是值传递
    unique_ptr<Thread> consumer1(new Thread(std::bind(&Consumer::consumer
                                            ,Consumer(),std::ref(taskque))));//ref是值传递

    producer1->start();
    consumer1->start();


    producer1->join();
    consumer1->join();

return 0; 
}

