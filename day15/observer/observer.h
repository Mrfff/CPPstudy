#pragma once
#include <iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

class Observer
{
public:
    virtual void update()=0 ;//用来修改消息
    ~Observer() {}

};

class Baby
:public Observer
{
public:
    Baby(const string &name)
    :_name(name){}

    void update() override;
private:
    string _name;
};

class Nurse
:public Observer
{
public:
    Nurse(const string &name)
    :_name(name)
    {}
    void update()override;
private:
    string _name;
};

class Ring;

class Guest
{
public:
    Guest(const string &name)
    :_name(name)
    {}

    void knock(Ring &ring);

private:
    string _name;
};
