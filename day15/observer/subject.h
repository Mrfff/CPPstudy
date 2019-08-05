#pragma once
#include<iostream>
#include<list>
using std::cout;
using std::endl;
using std::list;

class Observer;

class Subject
{
public:
    virtual void attach(Observer *ob)=0;
    virtual void detach(Observer *ob)=0;
    virtual void notify()=0;
    
    virtual ~Subject() {}
};

class Ring
:public Subject
{
public:
    Ring():_isRing(false){}
    void alarm();
    void attach(Observer *ob)override;
    void detach(Observer *ob)override;
    void notify()override;
private:
    bool _isRing;
    list<Observer*> _oblist;
};
