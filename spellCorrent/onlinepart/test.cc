#include"../include/Myconf.h"
#include"../include/Mydict.h"
#include"../include/WorkTask.h"
#include"../include/MyResult.h"

using namespace wd;

int main()
{
    //Myconf::getInstance("../conf/server.conf");
    Mydict::getInstance()->init("../conf/server.conf");
#if 0
    for(auto &elem:test1)
    {
        os<<elem.first<<" "<<elem.second<<endl;

    }
#endif

#if 0
    for(auto &elem:test2)
    {
        os<<elem.first<<" ";
        for(auto &s:elem.second)
        {
            os<<s<<" ";
        }
        os<<endl;
    }
#endif
    WorkTask worktest("Ad",20);
    worktest.execute();
    MyResult resulttest;
    cout<<"word is "<<resulttest._word<<endl;
    cout<<"frequent is "<<resulttest._iFreq<<endl;
    cout<<"distance is  "<<resulttest._iDist<<endl;



}



