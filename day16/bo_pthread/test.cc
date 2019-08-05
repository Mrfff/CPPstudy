#include"pthread.h"
#include"Noncopyable.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
#include<memory>
#include<string>
using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace wd;
class Myclass
{
public:
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

};
void process(string)
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


int main()
{
    //unique_ptr<Thread> thread(new Thread(std::bind(&Myclass::run,Myclass())));
    unique_ptr<Thread> thread(new Thread(std::bind(process,"wwf")));
    thread->start();
    thread->join();

 
}
