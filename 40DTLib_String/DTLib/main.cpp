#include <iostream>
#include <SmartPointer.h>
#include "Exception.h"

#include "DynamicList.h"
#include "StaticList.h"

#include "Sort.h"
#include "DTstring.h"

using namespace std;
using namespace DTLib;

int main()
{

    String s = "   abc    ";

    if(s.trim().insert(0,"D.T.").endof("abc") && s.startWith("D.T."))
    {
        cout << s.str() << endl;
    }

    return 0;
}

