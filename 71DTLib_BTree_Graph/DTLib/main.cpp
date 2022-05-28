#include <iostream>
#include "Graph.h"

using namespace std;
using namespace DTLib;

int main()
{
    Graph<int,int>* g = NULL;//抽象类不能定义对象，但是可以定义指针
    /*
     * 但是定义一个指针就不同了，指针是什么？
     * 大家都知道，无论它指向的是内部类型还是自己定义的结构体类型还是类的类型变量，
     * 它只不过就是一个具有32BIT也就是4个字节内存的空间而已，不需要其他任何信息了，所以能成功定义一个抽象类的指针变量*/
    Object* o = NULL;
    return 0;
}
