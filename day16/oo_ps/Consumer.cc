#include"Consumer.h"
#include"TaskQueue.h"


#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

template<class T>
void Consumer<T>::run()
{
    int i=10;
    while(i--)
    {
        int num=_que.pop();
        cout<<"Consumer thread "<<pthread_self()
            <<"   Consumer number  "<<num<<endl;
        
    }

}


