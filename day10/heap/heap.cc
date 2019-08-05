#include <iostream>
using std::cout;
using std::endl;

template<typename T,typename Compare=std::less<T>>
class HeapSort
{
public:
    void heapAdjust();
    void sort();
private:

};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

