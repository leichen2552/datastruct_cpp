#include <iostream>
#include "SharedPointer.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int value;

    Test():value(0)
    {
        cout << "Test()" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

int main()
{
    SharedPionter<Test> sp0 = new Test();

    sp0->value = 100;

    return 0;
}

