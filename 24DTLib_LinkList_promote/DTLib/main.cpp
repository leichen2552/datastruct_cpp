#include <iostream>
#include <cstring>
#include "LinkList.h"

using namespace std;
using namespace DTLib;

int main()
{

    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(0,i);
    }

    for(list.move(0); !list.end(); list.next())//这个操作的时间复杂度O(n2)
    {
        cout << list.current() << endl;//O(n)
    }


    return 0;
}

