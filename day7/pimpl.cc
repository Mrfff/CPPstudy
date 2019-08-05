#include <iostream>
#include"pimpl.h"
using std::cout;
using std::endl;
class Sumdata::SumdataImpl
{
    class Print
    {
    public:
        Print(int x,int y)
        :_x(x)
        ,_y(y)
        {
            cout<<"Print()"<<endl;
            
        };
        void printSum() const
        {
            int sum=_x+_y+_z;
            cout<<"the sum is "<<sum<<endl;
        }
        ~Print(){cout<<"~Print()"<<endl;};
    private:
        int _x;
        int _y;
        int _z;
    };
public:
    SumdataImpl(int x,int y)
    :_x(x,y)
    {
        cout<<"SumdataImpl(int x,int y)"<<endl;
    }
    void print()const
    {
        _x.printSum();
    }
    ~SumdataImpl(){cout<<"~Sumdata()"<<endl;};
private:
    Print _x;

};
Sumdata::Sumdata(int x,int y)
:_pimpl(new SumdataImpl(x,y))
{
    cout<<"Sumdata(int x,int y)"<<endl;
}
Sumdata::~Sumdata(){
    if(_pimpl)
    {
        delete _pimpl;
    }
}
void Sumdata::printSumdata() const
{
    _pimpl->print();

}
