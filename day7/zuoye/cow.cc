#include <iostream>
#include<string.h>
using std::cout;
using std::endl;
class Cow
{

public:
    Cow()
    :_pstr(new char[1+4]()+4)
    {
        *(int*)(_pstr-4)=1;
        cout<<"Cow()"<<endl;
    };

    Cow(const char *pstr)
    :_pstr(new char[5+strlen(pstr)]()+4)
    {
        refInit();
        strcpy(_pstr,pstr);

    };
    Cow(const Cow &rhs)
    :_pstr(rhs._pstr)
    {
        refAdd();
    }

    Cow &operator=(const Cow& rhs)
    {
        if(this!=&rhs)
        {
            refMinus();
            if(refNum()==0)
            {
            delete [](_pstr-4);
            cout<<"~Cow()"<<endl;
            }
            strcpy(_pstr,rhs._pstr);
            refAdd();    
        }
        return (*this);
    }
    ~Cow(){
        refMinus();
        if(refNum()==0)
        {
            delete [](_pstr-4);
            cout<<"~Cow()"<<endl;
        }
    };
    
friend std::ostream & operator<<(std::ostream &os,const Cow &rhs);
char & operator[](int index)
{
    if(index>0&&index<=(int)strlen(_pstr))
    {
        if(refNum()>1)
        {
            refMinus();
            char *temp=new char[strlen(_pstr)+5]()+4;
            strcpy(temp,_pstr);
            _pstr=temp;
            refInit();
        }
    return _pstr[index];
    }
    else
    {
        static char nullchar='\0';
        return nullchar;
    }
}

    int refNum() const
    {
        return *(int*)(_pstr-4);
    }
    
    void refInit()
    {
        *(int*)(_pstr-4)=1;
        
    }
    
    void refAdd()
    {
        ++(*(int*)(_pstr-4));

    }
    
    void refMinus()
    {
        --(*(int*)(_pstr-4));

    }

private:
    char *_pstr;
};

std::ostream & operator<<(std::ostream &os,const Cow &rhs)
{
    os<<rhs._pstr;
    return os;
}

int main()
{
    Cow s1="hello word";
    Cow s2=s1;
    cout<<"s1"<<s1<<endl;
    cout<<"s2"<<s2<<endl;
    
    return 0;
}

