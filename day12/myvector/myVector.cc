#include <iostream>
#include<algorithm>
#include<string>
#include<memory>
using std::endl;
using std::cout;
using std::string;
using std::allocator;
template<class Type>
class Vector
{
    public:
        using const_iterator= const Type *;
        Vector()
        :_start(nullptr)
        ,_finish(nullptr)
        ,_end_of_storage(nullptr){}
        ~Vector()
        {   
            if(size()>0)
            {
                while(_start!=_finish)
                {
                    _alloc.destroy(--_finish);
                }
                _alloc.deallocate(_start,capicity());

            }
            cout<<"clear over"<<endl;
        }
        size_t size()const{return _finish - _start;};
        size_t capicity()const {return _end_of_storage - _start;};
        void push_back(const Type &value);
        void pop_back();
        const_iterator begin() const{return _start;}
        const_iterator end() const{return _finish;}
        //void print(const Type &);
    private:
        void reallocate();//重新开辟空间
    private:
        static allocator<Type> _alloc;
        Type *_start;
        Type *_finish;
        Type *_end_of_storage;
};
template<class Type>
allocator<Type> Vector<Type>::_alloc;//初始化静态变量

template<class Type>
void Vector<Type>::push_back(const Type &value)
{
    if(size()==capicity())
    {
        reallocate();//满了从新开辟空间
    }
    _alloc.construct(_finish++,value);

}

template<class Type>
void Vector<Type>::pop_back()
{
    if(size()!=0)
    {
        _alloc.destroy(--_finish);
    }
}

template<class Type>
void Vector<Type>::reallocate()
{
    size_t cap=capicity();
    size_t realcap=2*cap>0 ? 2*cap:1;
    Type *p=_alloc.allocate(realcap);
    if(_start)
    {
        std::uninitialized_copy(_start,_finish,p);
    
    while(_start!=_finish)
    {
        _alloc.destroy(--_finish);//施放每一个存储的数据
    }
        _alloc.deallocate(_start,cap);//释放申请的空间；
    }
    _start=p;
    _finish=_start+cap;
    _end_of_storage=_start+realcap;
}

template<class T>
void print(const T &p)
{
    typename T::const_iterator it=p.begin();
    while(it!=p.end())
    {
        cout<<*it<<endl;
        ++it;
    }
    cout<<"the size = "<<p.size()<<endl;
    cout<<"the capicity = "<<p.capicity()<<endl;

}



int main()
{
    
    Vector<string> s;
    print(s);
    s.push_back("sdasd");
    s.push_back("sasd");
    s.push_back("ssd");
    s.push_back("sd");
    s.push_back("s");
    print(s);
    return 0;
}

