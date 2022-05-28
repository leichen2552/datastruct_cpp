#include <iostream>
#include <SmartPointer.h>
#include "Exception.h"

#include "DynamicList.h"
#include "StaticList.h"

using namespace std;
using namespace DTLib;

int main()
{
    StaticList<int,5> l;

    for(int i=0; i<l.capacity(); i++)
    {
        l[i] = i*i;//这行代码是想把线性表当做数组误用，线性表必须先插入元素，才能使用操作符[]访问元素，需要开发数组类
    }

    return 0;

}

