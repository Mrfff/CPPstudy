#include"TaskQueue.h"
#include"Producer.h"
#include"Consumer.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
#include<memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace wd;

int main()
{
    TaskQueue taskque(10);
    unique_ptr<Thread> producer(new Producer(taskque));
    unique_ptr<Thread> consumer(new Consumer(taskque));

    producer->start();
    consumer->start();


    producer->join();
    consumer->join();

return 0; 
}

