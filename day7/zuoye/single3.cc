#include <iostream>
#include<stdlib.h>
#include<pthread.h>
using std::cout;
using std::endl;

class Single
{
public:
    //直接从pthread_once中获取函数方式
    static Single *singleInstance()
    {
        pthread_once(&_once,init);
            return _pstr;
    }
    static void destroy()
    {
        if(_pstr)
        {
            delete _pstr;
        }
    }
    void print()const
    {
        cout<<" void print()const"<<endl;
    }
    //获取init函数,初始化pthread_once中第一个参数
    static void init()
    {
        _pstr=new Single();
        atexit(destroy);
    }
private:
    Single(){cout<<"Single()"<<endl;};
    ~Single(){cout<<"~Single()"<<endl;};
private:
    static Single *_pstr;
    static pthread_once_t _once;
};
Single * Single::_pstr=nullptr;
pthread_once_t Single::_once=PTHREAD_ONCE_INIT;
int main()
{
    Single::singleInstance()->print();
    return 0;
}

