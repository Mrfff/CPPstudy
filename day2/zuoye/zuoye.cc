#include <iostream>
#include<string.h>
//#include<string>
using std::cout;
using std::endl;
class String
{
public:
    String();
    String(const char *pstr);
    String(const String &rhs);
    String &operator=(const String &rhs)
    {
        cout<<"String &operator=(const String &rhs)"<<endl;
        if(this==&rhs)
        return (*this);

        delete []_pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        if(_pstr!=NULL)
        {
            strcpy(_pstr,rhs._pstr);
        }
        return(*this);
    }
    ~String()
    {
        delete []_pstr;
        cout<<"~String"<<endl;
    }
    void print();
    //{
    //cout<<"I am print"<<endl;

    //}
private:
    char *_pstr;
};
void String::print()
{
    cout<<"I am print:"<<_pstr<<endl;
    
}
String::String(const char *p)
    :_pstr(new char[strlen(p)+1]())
{
    strcpy(_pstr,p);
    cout<<"String(const char *p)"<<endl;
}
String::String()
{
    //_pstr=nullptr;
    _pstr=new char[20]();
    cout<<"I am String:"<<endl;
}
String::String(const String &rhs) 
    :_pstr(new char[strlen(rhs._pstr)+1]())
{
        strcpy(_pstr,rhs._pstr);
        cout<<"String(const String &rhs)"<<endl;

}
int main()
{
    String str1;
    str1.print();
    String str2="hello,world";
    String str3=("wangdao");
    str2.print();
    str3.print();
    String str4=str2;
    str4.print();
    return 0;
}

