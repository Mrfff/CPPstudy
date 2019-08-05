#include <iostream>
#include<math.h>
using std::endl;
using std::cout;
class Figure
{
public:
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
    
    double area(){return 3.14159*_r*_r;}
private:
    double _r;
};

void display(Figure *fig)
{
    fig->display();
    cout<<"area is "<<fig->area()<<endl;
}

//静态工厂模式
class Factory
{
public:
    static Circle createCircle()
    {
        Circle circle(10);
        return circle;
    }
};


int main()
{
    Circle circle=Factory::createCircle();
    display(&circle);
}
