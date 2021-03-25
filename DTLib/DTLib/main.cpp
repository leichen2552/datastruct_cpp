#include <iostream>
#include <SmartPointer.h>
#include "Exception.h"

using namespace std;
using namespace DTLib;

class Test
{
public:
    Test()
    {
        cout << "Test()" <<endl;
    }
    ~Test()
    {
        cout << "~Test()" <<endl;
    }
};

int main()
{
    try
    {
        THROW_EXCEPTION(ArithmeticException, "test");
    }
    catch(const ArithmeticException& e)//根据赋值兼容性原则，父类的catch语句要放在下面，子类的catch要放在上面
    {
        cout << "catch(const ArithmeticException e)" <<endl;
        cout << e.message() <<endl;
        cout << e.location() <<endl;
    }
    catch(const NullPointerException& e)//根据赋值兼容性原则，父类的catch语句要放在下面，子类的catch要放在上面
    {
        cout << "catch(const NullPointerException e)" <<endl;
        cout << e.message() <<endl;
        cout << e.location() <<endl;
    }
    catch(const IndexOutOfBoundsException& e)//根据赋值兼容性原则，父类的catch语句要放在下面，子类的catch要放在上面
    {
        cout << "catch(const IndexOutOfBoundsException e)" <<endl;
        cout << e.message() <<endl;
        cout << e.location() <<endl;
    }
    catch(const NoEnoughMemoryException& e)//根据赋值兼容性原则，父类的catch语句要放在下面，子类的catch要放在上面
    {
        cout << "catch(const NoEnoughMemoryException e)" <<endl;
        cout << e.message() <<endl;
        cout << e.location() <<endl;
    }
    catch(const InvalidParameterException& e)//根据赋值兼容性原则，父类的catch语句要放在下面，子类的catch要放在上面
    {
        cout << "catch(const InvalidParameterException e)" <<endl;
        cout << e.message() <<endl;
        cout << e.location() <<endl;
    }
    catch(const Exception& e)//因为这个是继承关系，根据赋值兼容性原则，子类对象可以出现在任何父类对象出现的地方
    {
        cout << "catch(const Exception e)" <<endl;
        cout << e.message() <<endl;
        cout << e.location() <<endl;
    }

    return 0;
}

