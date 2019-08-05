#include"Consumer.h"
#include"TaskQueue.h"


#include <iostream>
using std::cout;
using std::endl;

namespace wd{
void Consumer::run()
{
    int i=10;
    while(i--)
    {
        int num=_que.pop();
        cout<<"Consumer thread "<<pthread_self()
            <<"   Consumer number  "<<num<<endl;
        
    }

}

}//end of wd
