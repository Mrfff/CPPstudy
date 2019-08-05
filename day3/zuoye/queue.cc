#include <iostream>
using std::cout;
using std::endl;
class Queue
{
public:
    Queue()
        :_perpos(0)
        ,_backpos(0){}
       ~Queue(){}
    bool empty()
    {
        if(_backpos==_perpos)
        {
            cout<<"Que is empty"<<endl;
            return true;  
        }else return false;
    }
    bool full()
    {
        if(_backpos==max)
        {
            cout<<"Queue is full"<<endl;
            return true;
        }else return false;
    }
    void push(int a)
    {
        if(full())
        {
            return ;
        }
        _arry[_backpos++]=a; 
    }
    void pop()
    {
        if(empty())
        {
            return ;
        }
        _perpos++;

    }
    int front()
    {
        return _arry[_perpos];
    }
    int back()
    {
        return _arry[_backpos];
    }
private:
    static const int max=10;
    int _perpos;
    int _backpos;
    int _arry[max];
};

int main()
{
    Queue q;
    q.push(1);
    q.push(2);
    cout<<"get head"<<q.front()<<endl;
    q.push(3);
    q.push(4);
    q.pop();
    q.pop();
    cout<<"get head"<<q.front()<<endl;
    q.push(5);
    q.push(5);
    q.push(5);
    q.push(5);
    q.push(5);
    q.push(5);
    q.push(6);
    return 0;
}

