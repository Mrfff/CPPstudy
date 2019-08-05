#include <iostream>
using std::cout;
using std::endl;

class Single
{
    class Autorelease
    {
    public:
        Autorelease(){};
        ~Autorelease()
        {
               _pstr->destroy();
                cout<<" ~Autorelease()"<<endl;
        }

    };
public:
    static Single *singleInstance()
    {
        if(_pstr==nullptr)
        _pstr=new Single();
        return _pstr;
    }
    void destroy()
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
    static Autorelease _autorelease; 
};
Single * Single::_pstr=nullptr;
Single::Autorelease Single::_autorelease; 
int main()
{
    Single::singleInstance()->print();
    return 0;
}

