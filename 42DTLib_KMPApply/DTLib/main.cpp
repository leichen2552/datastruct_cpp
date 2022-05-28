#include <iostream>
#include <cstring>
#include "DTstring.h"

using namespace std;
using namespace DTLib;



int main()
{
    String s = "ababax";

    String s1 = s.sub(3,2);

    cout << s.str() <<endl;
    cout << s1.str() <<endl;


    return 0;
}

