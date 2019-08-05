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

template<class T>
class Single
: public T
{
public:
    template<typename T1, typename T2>
    static Single<T> *getInstance(T1  item1, T2 item2)
    {
        if(_pInstance==nullptr)
        {
            _pInstance=new Single(item1, item2);
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
    template<typename T1, typename T2>
    Single(T1 item1, T2 item2)
    :T(item1, item2){
        cout << "Single(T1,T2)" << endl;
    }
    ~Single(){
        cout << "~Single()" << endl;
    }
private:
    static Single<T> *_pInstance;
};
template<class T>
Single<T> *Single<T>::_pInstance=nullptr;
//Single<Type> * Single::_pInstance = nullptr;
int main()
{
     Computer * p1 = Single<Computer>::getInstance("Xiaomi", 6666);
    p1->print();
     Computer * p2 = Single<Computer>::getInstance("Xiaomi", 6666);
    p2->print();

    return 0;
}

