#include <iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

template<class Type,int size=10>
class Queue
{
public:
    Queue()
    :_head(0)
    ,_rear(0)
    ,_base(new Type[size]())
    {};
    ~Queue();
    bool full() const;
    bool empty() const;
    void push(const Type &value);
    void pop();
    const Type & front() const;
    const Type & back() const;
private:
    int _head;
    int _rear;
    Type *_base;
};

template<class Type,int size>
Queue<Type,size>::~Queue()
{
    if(_base)
    {
        delete []_base;
        _base=nullptr;
    }
}

template<class Type,int size>
bool Queue<Type,size>::full() const
{
    if(_head==(_rear+1)%size)
    {
        return true;
    }
    else
    {
        return false;
    }

}

template<class Type,int size>
bool Queue<Type,size>::empty() const
{
    if(_head==_rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Type,int size>
void Queue<Type,size>::push(const Type & value)
{
    if(!full())
    {
        _base[_rear++]= value;
        _rear%=size;
        
    }
    else
    {
        cout<<"queue is full"<<endl;
    }
}
template<class Type,int size>
void Queue<Type,size>::pop()
{
    if(!empty())
    {
        ++_head;
        _head%=size;

    }
    else
    {
        cout<<"queue is empty"<<endl;
    }
}

template<class Type,int size>
const Type & Queue<Type,size>::front() const
{
    return _base[_head];
}

template<class Type,int size>
const Type & Queue<Type,size>::back() const
{
    return _base[(_rear-1+size)%size];
}

int main()
{
#if 0
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.push(6);
    cout<<"the front "<<queue.front()<<endl;
    cout<<"the back "<<queue.back()<<endl;
    while(!queue.empty())
    {
        cout<<queue.front()<<endl;
        queue.pop();
    }
#endif
    Queue<string> queue;
    queue.push("a");
    queue.push("b");
    queue.push("c");
    queue.push("d");
    queue.push("e");
    queue.push("f");
    queue.push("g");
    queue.push("h");
    cout<<"the front "<<queue.front()<<endl;
    cout<<"the back "<<queue.back()<<endl;
    while(!queue.empty())
    {
        cout<<queue.front()<<endl;
        queue.pop();
    }
    return 0;
}

