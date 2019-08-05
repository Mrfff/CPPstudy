#include <iostream>
#include<string.h>
using std::cout;
using std::endl;
class Stack
{
public:
    Stack(int id,const char * name)
    :_name(new char[strlen(name)+1]())
    ,_id(id)
    {
        strcpy(_name,name);
    }
    ~Stack()
    {
        delete[] _name;
    }
    void print()
    {
        cout<<"id:"<<_id<<"         "<<_name<<endl;
    }
private:
    static void *operator new(size_t sz){
        return malloc(sz);
    }
    static void operator delete(void *p)
    {
        free(p);
    }
private:
    char* _name;
    int _id;
};
int main()
{
    //Stack *p=new Stack(1,"wwf");
    //p->print();
    //delete p;
    Stack p1(2,"lq");
    p1.print();
    return 0;
}

