#include <iostream>
#include <cstring>
#include "DTstring.h"

#include "StaticArray.h"

using namespace std;
using namespace DTLib;

int main()
{
    StaticArray<int,5> s1;

    for(int i=0; i<s1.length();i++)
    {
        s1[i] = i*i;
    }

    for(int i=0; i<s1.length();i++)
    {
        cout << s1[i] << endl;
    }

    StaticArray<int,5> s2;

    s2 = s1;

    for(int i=0; i<s2.length();i++)
    {
        cout << s2[i] << endl;
    }

    s2[6] = 100;//越界会产生异常

    int s3[5];

    s3[6] = 100;//原生数组就不会报错，到底会在什么时候处bug不得而知

    return 0;
}

