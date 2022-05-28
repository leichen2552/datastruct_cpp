#include <iostream>
#include "CircleList.h"

using namespace std;
using namespace DTLib;

void josephus(int n, int s, int m)
{
    CircleList<int> cl;

    for(int i=1; i<=n; i++)
    {
        cl.insert(i);
    }


    cl.move(s-1, m-1);//报数到m，就移动到m-1次

    while (cl.length() > 0)
    {
        cl.next();

        cout << cl.current() << endl;

        cl.remove(cl.find(cl.current()));
    }
}

int main()
{
    josephus(41, 1, 3);

    return 0;
}

