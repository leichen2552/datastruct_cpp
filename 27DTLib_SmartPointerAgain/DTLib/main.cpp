#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    Test()
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
    SmartPointer<Test> sp = new Test();

    SmartPointer<Test> spn;

    spn = sp;

    return 0;
}

