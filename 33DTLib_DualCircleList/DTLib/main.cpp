#include <iostream>
#include "DualCircleList.h"

using namespace std;
using namespace DTLib;


int main()
{
    DualCircleList<int> dl;

    int i =0;

    for(i=0; i<5; i++)
    {
        dl.insert(i);
        dl.insert(5);
    }


    cout << "begin" << endl;

    dl.move(dl.length() - 1);

    while (dl.find(5) != -1)
    {
        if(dl.current() == 5)
        {
            cout << dl.current() <<endl;

            dl.remove(dl.find(dl.current()));
        }
        else
        {
            dl.pre();
        }
    }

    i =0;

    //for(dl.move(0); !dl.end(); dl.next())//游标访问时间复杂度降低,打印出来是双向循环链表不可能结束
    //for(int i=0; i<10; i++)
    for(dl.move(dl.length() - 1); (i < dl.length()) && !dl.end(); dl.pre(), i++)
    {
        cout << dl.current() << endl;
    }

    return 0;
}
