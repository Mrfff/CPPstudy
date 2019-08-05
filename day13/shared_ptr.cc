#include <iostream>
#include<memory>
using std::cout;
using std::endl;
using std::shared_ptr;

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
            <<")";
    return os;
}
void test0()
{
    Point *pt=new Point(1,2);
    shared_ptr<Point> sp(pt);
    shared_ptr<Point> sp2(pt);
    cout<<"sp" <<*sp<<endl;
    cout<<"sp2"<<*sp2<<endl;
}

int main()
{
    test0();
    return 0;
}

