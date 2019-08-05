#include"subject.h"
#include"observer.h"
#include<algorithm>

void Ring::alarm()
{
    if(!_isRing)
    {
        _isRing=true;
        notify();//通知
        _isRing=false;
    }

}

void Ring::attach(Observer *ob)
{
    auto it=std::find(_oblist.begin(),_oblist.end(),ob);
    if(it==_oblist.end())
    {
        _oblist.push_back(ob);
    }
}

void Ring::detach(Observer *ob)
{
    auto it=std::find(_oblist.begin(),_oblist.end(),ob);
    if(it!=_oblist.end())
    {
        _oblist.erase(it);
    }
}

void Ring::notify()
{
    for(auto &ob:_oblist)
    {
        ob->update();
    }
}
