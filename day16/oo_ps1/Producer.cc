#include"Producer.h"
#include"TaskQueue.h"

#include<unistd.h>
#include<stdlib.h>

#include <iostream>

using std::endl;
using std::cout;

namespace wd{

void Producer::run()
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

}//end of wd
