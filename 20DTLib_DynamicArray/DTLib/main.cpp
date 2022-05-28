#include <iostream>
#include <cstring>
#include "DTstring.h"

#include "StaticArray.h"
#include "DynamicArray.h"

using namespace std;
using namespace DTLib;

int main()
{
    DynamicArray<int> s1(5);

    for(int i=0; i<s1.length();i++)
    {
        s1[i] = i*i;
    }

    for(int i=0; i<s1.length();i++)
    {
        cout << s1[i] << endl;
    }

    DynamicArray<int> s2(10);

    s2 = s1;

    for(int i=0; i<s2.length();i++)
    {
        cout << s2[i] << endl;
    }

    s2.resize(3);

    for(int i=0; i<s2.length();i++)
    {
        cout << s2[i] << endl;
    }

    //s2[6] = 100;//越界会产生异常

//    int s3[5];

//    s3[6] = 100;//原生数组就不会报错，到底会在什么时候处bug不得而知

    return 0;
}

