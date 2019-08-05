#include <iostream>
#include<string.h>
using std::cout;
using std::endl;
class Cow
{

    class Charcow
    {
    public:
        Charcow(Cow &self,int index)
            :_self(self)
             ,_index(index)
        {
            cout<<"Charcow(Cow &self,int index)"<<endl;
        };
        char &operator=(const char &ch)
        {
            if(_index>0&&_index<=_self.size())
            {
                if(_self.refNum()>1)
                {
                    _self.refMinus();
                    char *temp=new char[_self.size()+5]()+4;
                    strcpy(temp,_self._pstr);
                    _self._pstr=temp;
                    _self.refInit();
                }
                _self._pstr[_index]=ch;
                return _self._pstr[_index];
            }
            else
            {
                static char nullchar='\0';
                return nullchar;
            }

        }
        friend std::ostream &operator<<(std::ostream &os,const Charcow &rhs);
        //friend std::ostream &operator<<(std::ostream &os,const Cow &rhs);
    private:
        Cow &_self;
        int _index;
    };
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
    friend std::ostream &operator<<(std::ostream &os,const Charcow &rhs);

    Charcow operator[](int index)
    {
        return Charcow(*this,index);    
    };
    /*char & operator[](int index)
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
      */
     int size()const {return sizeof(_pstr);} 
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
std::ostream & operator<<(std::ostream &os,const Cow::Charcow &rhs)
{
    os<<rhs._self._pstr[rhs._index];
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

