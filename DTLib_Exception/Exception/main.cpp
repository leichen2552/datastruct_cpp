#include <iostream>

using namespace std;

double divide(double a, double b)
{
    const double delta = 0.00000000001;
    double ret = 0;

    if( !((-delta < b) && (b < delta)) )
    {
        ret = a / b;
    }
    else
    {
        throw 0; //²úÉú³ý 0 Òì³£
    }

    return ret;

}

void Demo()
{
    try
    {
        throw 1;
    }
    catch(int i)
    {
        cout << "catch(int i)" << endl;
    }
    catch(double d)
    {
        cout << "catch(double d)" << endl;
    }
    catch(char c)
    {
        cout << "catch(char c)" << endl;
    }

}

int main()
{
    cout << "main Begin" << endl;

    Demo();

    try
    {
        double c = divide(1, 0);
        cout << "c = " << c << endl;
    }
    catch(...)
    {
        cout << "Divided by Zero..." << endl;
    }

    cout << "main end" << endl;

    return 0;
}

