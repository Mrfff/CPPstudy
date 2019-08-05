#include "observer.h"
#include"subject.h"
#include<stdlib.h>
#include<iostream>

using std::cout;
using std::endl;

void Baby::update()
{
    ::srand(::clock());
    int num=::rand()%100;
    if(num<70)
    {
        cout<<"baby "<<_name
            <<" is sleeping"<<endl;

    }else
    {
        cout<<"baby "<<_name
            <<" is cring~"<<endl;
    }
}

void Nurse::update()
{
    ::srand(::clock());
    int num=::rand()%100;
    if(num>70)
    {
        cout<<"Nurse "<<_name
            <<" is starting opening the door"<<endl;
    }else
    {
        cout<<"Nurse "<<_name
            <<" is sleeping"<<endl;
    }
}

void Guest::knock(Ring &ring)
{
    cout<<"Guest "<<_name
        <<" is knoing at the door"<<endl;
    ring.alarm();   
};
