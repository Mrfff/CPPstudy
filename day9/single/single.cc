#include <iostream>
#include<string>
using std::string;
using std::endl;
using std::cout;
class Point
    {
    public:
        Point(int x,int y)
        :_x(x)
        ,_y(y)
        {
        }
        ~Point()
        {}
        void print()
        {
            cout<<_x<<"     "<<_y<<endl;
        }
    private:
        int _x;
        int _y;
    };

class Computer
{
public:
    Computer(const char * name,int price)
    :_name(name)
    ,_price(price)
    {}
    ~Computer(){}
    void print()
    {
        cout<<_name<<"    "<<_price<<endl;
    }
private:
    string _name;
    int _price;

};

template<class Type>
class Single
{
public:
    template<class ...Args>
    static Type *getInstance(Args... args)
    {
        if(_pInstance==nullptr)
        {
            _pInstance=new Type(args...);
        }
        return _pInstance;
    }
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance=nullptr;
        }
    }
private:
    Single();
    ~Single();
private:
    static Type *_pInstance;
};
template<class Type>
Type *Single<Type>::_pInstance=nullptr;
//Single<Type> * Single::_pInstance = nullptr;
int main()
{
#if 1
     Computer * p1 = Single<Computer>::getInstance("Xiaomi", 6666);
    p1->print();
     Computer * p2 = Single<Computer>::getInstance("Xiaomi", 6666);
    p2->print();
#endif
     Point* p3 = Single<Point>::getInstance(1, 2);
    p3->print();
     Point * p4 = Single<Point>::getInstance(1, 2);
    p4->print();
    return 0;
}

