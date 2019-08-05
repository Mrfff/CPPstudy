#include <iostream>
#include<string.h>
using std::cout;
using std::endl;
class Person
{
public:
    Person(const char *name,int age)
    :_name(new char [20]())
    ,_age(age)
    {
        strcpy(_name,name);
        //cout<<"Person()"<<endl;
    }
    void display()
    {
        cout<<"name: "<<_name<<"    ";
        cout<<"age: "<<_age<<endl;
    }

    ~Person()
    {
        delete []_name;
        //cout<<"~Person()"<<endl;
    }
private:
    char *_name;
    int _age;

};
class Employee:public Person
{
public:
    Employee(const char*name,int age,const char *departmant,double salary)
    :Person(name,age)
    ,_departmant(new char[strlen(departmant)+1]())
    ,_salary(salary)
    {
        strcpy(_departmant,departmant);
        //cout<<" Employee(char*name,int age, char *departmant,double salary)"<<endl;
    }
    void display()
    {
        Person::display();
        cout<<"departmant: "<<_departmant<<"    ";
        cout<<"salary: "<<_salary<<endl;
    }
    ~Employee()
    {
        delete []_departmant;
       // cout<<"~Employee()"<<endl;
    }
private:
    char *_departmant;
    double _salary;
};


int main()
{
    Employee a("wwf",10,"A",10000);
    Employee b("lq",10,"A",6000);
    Employee c("lsy",10,"A",4000);
    a.display();
    b.display();
    c.display();
    return 0;
}

