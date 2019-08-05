#include <iostream>
using std::cout;
using std::endl;
class Circle
{
public:
    Circle()
    :_r(0.0)
    {
        cout<<"set r=0.0 sucess"<<endl;
    }
    Circle(double r)
    :_r(r)
    {
        cout<<"get the r sucess"<<endl;
    }
    double getArea()
    {
        return _r*_r*3.14;
    }
    
    double getPerimeter()
    {
        return 2*_r*3.14;
    }

    void show()
    {
        cout<<"The area = "<<getArea()<<endl;
        cout<<"The perimeter = "<<getPerimeter()<<endl;
    }
private:
    double _r;
};
class Cylinder
:public Circle
{
public: Cylinder (double r,double h)
        :Circle(r)
        ,_h(h)
        {
        cout<<"Cyliner(double r,double h)"<<endl;
        }
        double getVoulume()
        {
            return getArea()*_h;
        }
        void showVolume()
        {
            cout<<"The volume = "<<getVoulume()<<endl;
        }

private:
    double _h;
};

int main()
{
    Circle c(3);
    c.show();
    Cylinder v(3,4);
    v.show();
    v.showVolume();
    return 0;
}

