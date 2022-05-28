#include <iostream>
#include <ctime>
#include <SmartPointer.h>
#include "Exception.h"

#include "DynamicList.h"
#include "StaticList.h"

#include "Sort.h"

using namespace std;
using namespace DTLib;

struct Test : public Object
{
    int id;
    int data1[1000];
    double data2[500];

    bool operator <(const Test& obj)
    {
        return id < obj.id;
    }

    bool operator >(const Test& obj)
    {
        return id > obj.id;
    }

    bool operator <=(const Test& obj)
    {
        return id <= obj.id;
    }

    bool operator >=(const Test& obj)
    {
        return id >= obj.id;
    }
};

class TestProxy :public Object
{
protected:
    Test* m_pTest;
public:
//    TestProxy(Test* pTest)
//    {
//        m_pTest = pTest;
//    }

    int id()
    {
        return m_pTest->id;
    }

    int* data1()
    {
        return m_pTest->data1;
    }

    double* data2()
    {
        return m_pTest->data2;
    }

    Test& test()const
    {
        return *m_pTest;
    }
/*    之前的直接比较id
    bool operator <(const TestProxy& obj)
    {
        return id < obj.id;
    }

    bool operator >(const TestProxy& obj)
    {
        return id > obj.id;
    }

    bool operator <=(const TestProxy& obj)
    {
        return id <= obj.id;
    }

    bool operator >=(const TestProxy& obj)
    {
        return id >= obj.id;
    }的比较
*/
//代理模式
    bool operator <(const TestProxy& obj)
    {
        return test() < obj.test();
    }

    bool operator >(const TestProxy& obj)
    {
        return test() > obj.test();
    }

    bool operator <=(const TestProxy& obj)
    {
        return test() <= obj.test();
    }

    bool operator >=(const TestProxy& obj)
    {
        return test() >= obj.test();
    }

    Test& operator =(Test& test)
    {
        m_pTest = &test;

        return test;
    }
};

Test t[1000];
TestProxy pt[1000];

int main()
{
    clock_t begin = 0;
    clock_t end = 0;

    for(int i=0; i<1000; i++)
    {
        t[i].id = i;
        pt[i] = t[i];
    }

    begin = clock();

    Sort::Bubble(t, 1000, false);//time = 780
    Sort::Bubble(pt, 1000, false);//time = 14

    end = clock();


    cout << "Time1 = "<< end - begin << endl;
    return 0;
}

