#include <iostream>
#include "StaticQuene.h"

using namespace std;
using namespace DTLib;



int main()
{
    StaticQuene<int, 5> quene;

    for(int i=0; i<5; i++)
    {
        quene.add(i);
    }
    while (quene.length() > 0)
    {
        cout << quene.front() <<endl;

        quene.remove();
    }

    return 0;
}
