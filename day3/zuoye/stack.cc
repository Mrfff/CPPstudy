#include <iostream>
using std::cout;
using std::endl;

class Stack
{
public:
    Stack()
        :_nowNum(0)
    {cout<<"Initstack OK"<<endl;}
    ~Stack(){}
    int  top(){return _arry[_nowNum-1];};
    bool empty(){if(_nowNum==0)return true;else return false;};
    bool full(){if(_nowNum==max)return true;else return false;};
    void push(int a)
    {
        if(full())
        {
            cout<<"stack is full"<<endl;
            exit(0);
        }
            
            _arry[_nowNum++]=a;
           //_nowNum++;
           cout<<"now Num "<<_nowNum<<endl;
    }
    void pop()
    {
        if(empty())
        {
            cout<<"stack is empty"<<endl;
            exit(0);
        }
        _nowNum--;
    }
private:
    static const int max=10;
    int _arry[max];
    int _nowNum;
};

int main()
{
    Stack s;
    s.push(10);
    s.push(12);
    cout<<"top is "<<s.top()<<endl;
    s.push(12);
    s.push(12);
    s.push(12);
    s.push(12);
    s.push(12);

    return 0;
}

