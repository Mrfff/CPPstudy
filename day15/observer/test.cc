#include "observer.h"
#include "subject.h"
#include<memory>
using std::unique_ptr;


int main()
{
    unique_ptr<Observer> baby1(new Baby("wwf"));
    unique_ptr<Observer> baby2(new Baby("lq"));
    unique_ptr<Observer> nurse1(new Nurse("jzm"));
    unique_ptr<Observer> nurse2(new Nurse("wyh"));
    Ring ring;
    ring.attach(baby1.get());
    ring.attach(baby2.get());
    ring.attach(nurse1.get());
    ring.attach(nurse2.get());

    Guest guest("boss");
    guest.knock(ring);
    
    
    return 0;
}

