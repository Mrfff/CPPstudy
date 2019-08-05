#include <iostream>
//void print();
namespace wwf
{
 namespace lq
{
void print(void)
{
    using std::cout;
    using std::endl;
    cout<<"wwf::lq::printf"<<endl;
}
}
}
int main()
{
    using wwf::lq::print;
    print();
    std::cout << "Hello world" << std::endl;
    return 0;
}

