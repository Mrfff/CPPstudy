#include <iostream>
using std::endl;
using std::cout;

template<class Type>
class RAII
{
public:
    RAII(Type *point)
        :_point(point)
    {

    }
    Type *operator->()
    {
        return _point;
    }
    Type &operator*()
    {
        return *_point;
    }
    void reset(Type * point)
    {
        if(_point)
        {
            delete _point;
        }
        _point=point;
    }
    ~RAII()
    {
        if(_point)
        {delete _point;}
    }


private:
    Type *_point;
};
class Point
{
public:
    Point (int ix=0,int iy=0)
    :_ix(ix)
    ,_iy(iy)
    {cout<<"Point (int ,int)"<<endl;}
    void print()const
    {
        cout<<"("<<_ix
            <<","<<_iy
            <<")"<<endl;
    }
    ~Point(){}
    friend std::ostream &operator<<(std::ostream&os,const Point &rhs);
private:
    int _ix;
    int _iy;
};
std::ostream&operator<<(std::ostream &os,const Point &rhs)
{
        os<<"("<<rhs._ix
            <<","<<rhs._iy
            <<")"<<endl;
    return os;
}

int main(void)
{
    RAII<Point> point(new Point(1,2));
    point->print();
    (*point).print();
    cout<<*point;
}
