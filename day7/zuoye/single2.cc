#include <iostream>
#include<stdlib.h>
using std::cout;
using std::endl;

class Single
{
public:
    static Single *singleInstance()
    {
        if(_pstr==nullptr)
        {
        _pstr=new Single();
        atexit(destroy);
        }
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
private:
    Single(){cout<<"Single()"<<endl;};
    ~Single(){cout<<"~Single()"<<endl;};
private:
    static Single *_pstr;
};
Single * Single::_pstr=nullptr;
int main()
{
    Single::singleInstance()->print();
    return 0;
}

