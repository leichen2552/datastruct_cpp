#include <iostream>
#include <SmartPointer.h>
#include "Exception.h"

#include "DynamicList.h"
#include "StaticList.h"

#include "Sort.h"

using namespace std;
using namespace DTLib;

int main()
{
    int array[] = {7,3,5,2,1,4,6,9,8,9};

    Sort::Quick(array, 10);

    for(int i=0; i<10; i++)
    {
        cout<< array[i] << endl;
    }

    return 0;
}

