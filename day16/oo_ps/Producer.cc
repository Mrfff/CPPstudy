
#include"TaskQueue.h"
#include"Producer.h"

#include<unistd.h>
#include<stdlib.h>

#include <iostream>

using std::endl;
using std::cout;
using namespace wd;

template<class T>
void Producer<T>::run()
{
    ::srand(::time(nullptr));
    int i=10;
    while(i--)
    {
        int num=::rand()%100;
        _que.push(num);
        cout<<"Producer thread "<<pthread_self()
            <<"  :Producer the num "<<num<<endl;
    }

}


