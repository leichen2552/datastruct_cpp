#include <iostream>
#include <cstring>
#include "LinkList.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
    int i = 0;
public:
    Test(int v = 0)
    {
        i = v;
    }

    bool operator ==(const Test& obj)
    {
        return (i == obj.i);
    }
};

int main()
{
    Test t1(1);
    Test t2(2);
    Test t3(3);

    LinkList<Test> list;

    list.insert(t1);
    list.insert(t2);
    list.insert(t3);

//    for(int i=0; i<5; i++)
//    {
//       list.insert(0, i);
//    }

    cout << list.find(t2) << endl;


    return 0;
}

