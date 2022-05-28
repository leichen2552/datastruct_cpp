#include <iostream>
#include "LinuxLinkQuene.h"
#include "StaticQuene.h"

using namespace std;
using namespace DTLib;

class Test:public Object
{
public:
    Test() {cout << "Test()" << endl;}
    ~Test() {cout << "~Test()" << endl;}
};

int main()
{
    LinuxLinkQuene<Test> lq;
    StaticQuene<Test, 10> llq;

    for(int i=0; i<10; i++)
    {
        //lq.add(i);
    }

    while( lq.length() > 0 )
    {
        //cout << lq.front() << endl;

        lq.remove();
    }

    return 0;
}
