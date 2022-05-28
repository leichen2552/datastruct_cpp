#include <iostream>
#include "StaticStack.h"

using namespace std;
using namespace DTLib;


int main()
{
    StaticStack<int, 5> stack;

    try
    {
        stack.pop();
    }
    catch(const Exception& e)
    {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }


    for(int i=0; i<10; i++)
    {
        stack.push(i);
    }

    while(stack.size() > 0)
    {
        cout << stack.top() << endl;
        stack.pop();
    }

    return 0;
}
