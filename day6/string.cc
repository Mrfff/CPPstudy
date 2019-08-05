#include <iostream>
#include<string>
#include<string.h>
using std::endl;
using std::cout;
class String {
public:
    String()
    :_pstr(nullptr)
    {
        cout<<"String()"<<endl;
    };
    String(const char *pstr)
    :_pstr(new char[strlen(pstr)+1]())
    {
        strcpy(_pstr,pstr);
        cout<<"String(const char *pstr)"<<endl;
    }
    String(const String&rhs)
    :_pstr(new char[strlen(rhs._pstr)+1]())
    {
        strcpy(_pstr,rhs._pstr);
        cout<<" String(const String&rhs)"<<endl;
    };
    ~String()
    {
        if(_pstr)
        {
            delete[]_pstr;
            cout<<"~String()"<<endl;
        }
    };
    String &operator=(const String & rhs)
    {
        cout<<"String &operator=(const String & rhs)"<<endl;
        if(this==&rhs)
        {
        return (*this);
        }
        delete []_pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        if(_pstr!=NULL)
        {
            strcpy(_pstr,rhs._pstr);
        }
        return(*this);

    };
    String &operator=(const char *pstr)
    {
        delete []_pstr;
        _pstr=new char[strlen(pstr)+1]();
        if(_pstr!=NULL)
        {
            strcpy(_pstr,pstr);
        }
        return (*this);
    }

    String &operator+=(const String &pstr)
    {
        char *tmp=new char[strlen(_pstr)+1]();
        strcpy(tmp,_pstr);
        delete []_pstr;
        _pstr=new char[strlen(tmp)+strlen(pstr._pstr)+1]();
        strcpy(_pstr,tmp);
        strcat(_pstr,pstr._pstr);
        return (*this);
        delete []tmp;
        
    }
    String &operator+=(const char *pstr)
    {
        char *tmp=new char[strlen(_pstr)+1]();
        strcpy(tmp,_pstr);
        delete []_pstr;
        _pstr=new char[strlen(tmp)+strlen(pstr)+1]();
        strcpy(_pstr,tmp);
        strcat(_pstr,pstr);
        return (*this);
        delete []tmp;

    }
    char &operator[](std::size_t index)
    {
        static char szNull='\n';
        if(index>=0&&index<strlen(_pstr))
        {
            return _pstr[index];
        }else
        {
            cout<<"下标越界"<<endl;
            return szNull;
        }
    };
    const char &operator[](std::size_t index) const;

    std::size_t size() const;
    const char* c_str() const;

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char * _pstr;
};
bool operator==(const String &s1, const String &s2)
{
    cout<<"==operator"<<endl;
    if(strcmp(s1._pstr,s2._pstr)==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator!=(const String &s1, const String &s2)
{
    if(!strcmp(s1._pstr,s2._pstr))
    {
        return false;
    }else
    {
        return true;
    }
}
bool operator<(const String &s1, const String &s2)
{
    if(strcmp(s1._pstr,s2._pstr)<0)
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator>(const String &s1, const String &s2)
{
    if(strcmp(s1._pstr,s2._pstr)>0)
    {return true;}
    else
    {
        return false;
    }
}
bool operator<=(const String &s1, const String &s2)
{
    size_t s1len=strlen(s1._pstr);
    size_t s2len=strlen(s2._pstr);
    if(s1len<s2len&&(strncmp(s1._pstr,s2._pstr,s1len)==0))
    {
        return true;
    }
    else 
    {
        return false;
    }
}
  bool operator>=(const String &s1, const String &s2)
{
    size_t s1len=strlen(s1._pstr);
    size_t s2len=strlen(s2._pstr);
    if(s1len>s2len&&(strncmp(s1._pstr,s2._pstr,s2len)==0))
    {
        return true;
    }
    else 
    {
        return false;
    }

}
int main()
{
    String s1="asd";
    String s2="asdsd";
    if(s1<=s2){cout<<"<=重载成功"<<endl;}
    else{cout<<"失败"<<endl;}
    return 0;
}

