#include <iostream>
#include<math.h>
#include<memory>
using std::endl;
using std::cout;
using std::unique_ptr;
class Figure
{
public:
    ~Figure(){cout<<"~Figure"<<endl;}
    virtual void display()const =0;
    virtual double area()=0;
};

class Circle
: public Figure
{
public:
    Circle(double r):_r(r)
    {}
    void display()const
    { 
        cout<<"Circle";
    }
    ~Circle(){cout<<"Circle"<<endl;}
    double area(){return 3.14159*_r*_r;}
private:
    double _r;
};

void display(Figure *fig)
{
    fig->display();
    cout<<"area is "<<fig->area()<<endl;
}

//工厂模式
class Factory
{
public:
    virtual Figure *create()=0;//指向fig的指针
    virtual ~Factory(){cout<<"~Factory"<<endl;}
};

class FactoryCircle
:public Factory
{
public:
    Figure  *create()override
    {
        return new Circle(10);
    }
    ~FactoryCircle(){cout<<"~FactoryCircle"<<endl;}
};

int main()
{
    unique_ptr<Factory> factoryCircle(new FactoryCircle());
    unique_ptr<Figure> circle(factoryCircle->create());
    display(circle.get());
}
