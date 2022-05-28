#include <iostream>
#include <cstring>
#include "DTstring.h"

using namespace std;
using namespace DTLib;

//递归求和
unsigned int sum(unsigned int n )
{
    if(n > 1)
    {
        return n + sum(n - 1);
    }
    else
    {
        return 1;
    }
}


//斐波那契数列
unsigned int fac(unsigned int n )
{
    if(n > 2)
    {
        return (fac(n - 1) + fac(n - 2));
    }
    else
    {
        return 1;
    }
}

//递归求字符串长度
unsigned int _strlen(const char *s)
{
//    if(*s != '\0')
//    {
//        return 1 + _strlen(s+1);
//    }
//    else
//    {
//        return 0;
//    }

    return s ? (*s ? (1 + _strlen(s+1)) : 0) : 0;//比较难读，琢磨推敲的过程
}

int main()
{

    cout << sum(100) << endl;

    cout << fac(10) << endl;

    for(int i=1; i<11;i++)
    {
        cout << i << ":" << fac(i) << endl;
    }

    cout << _strlen("aabbcc") << endl;

    return 0;
}

