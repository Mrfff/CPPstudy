#include <iostream>
using std::cout;
using std::endl;
class Single
{
public:
    void print()
    {
        cout<<"print:"<<_data<<endl;
    } 
    static Single *getInit()
    {
        if(_point==nullptr)
        {
            cout<<"I am create new"<<endl;
            _point=new Single();
        }
        return _point;
    }
    static void destry()
    {
        if(_point!=NULL)
        {
        delete _point;
        cout<<"I have been deleted new"<<endl;
        }
    }
private:    
    Single()
        :_data(0)
    {
        cout<<"Single()"<<endl;
    }
    ~Single(){cout<<"~Single"<<endl;} 
private:
    int _data;
    static Single *_point;
    
};
Single *Single::_point=nullptr;
int main()
{
    Single *s=Single::getInit();
    Single::getInit()->print();
    cout<<"s:"<<s<<endl;
    Single::destry();

    return 0;
}

