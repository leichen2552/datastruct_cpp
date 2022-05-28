#include <iostream>
#include <cstring>
#include "LinkList.h"
#include "StaticLinkList.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main()
{

    StaticLinkList<int, 5> list;

    for(int i=0; i<5; i++)
    {
        list.insert(0,i);
    }

//    try
//    {
//        list.insert(6);//会报错，因为一开始就指定了5个
//    }
//    catch(const Exception& e)
//    {
//        cout << e.message() <<endl;
//    }


    for(list.move(0); !list.end(); list.next())//这个操作的时间复杂度O(n2)
    {
        cout << list.current() << endl;//O(n)
    }


    return 0;
}

