#include <iostream>
#include <cstring>
#include "LinkList.h"

using namespace std;
using namespace DTLib;

class Test
{
public:
    Test()
    {
        throw 0;
    }
};

int main()
{
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
       list.insert(i);
       //list.set(i, i*i);

       for(int j=0; j<list.length(); j++)
       {
          cout << list.get(j) << endl;
       }
       cout << endl;
    }



//    for(int i=0; i<list.length(); i++)
//    {
//       cout << list.get(i) << endl;
//    }

    cout << endl;
    cout << endl;
    list.remove(2);


    for(int i=0; i<list.length(); i++)
    {
       cout << list.get(i) << endl;
    }

//    for(int i=0; i<list.length(); i++)
//    {
//       cout << list.get(i) << endl;
//    }

//    list.clear();

//    for(int i=0; i<list.length(); i++)
//    {
//       cout << list.get(i) << endl;
//    }
       return 0;

}

