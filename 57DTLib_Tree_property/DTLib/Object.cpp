#include "Object.h"
#include <cstdlib>

namespace DTLib
{

void* Object::operator new (unsigned int size) throw()//这个异常重载说明就是这个函数不会抛出任何的exception
{
    return malloc(size);
}

void Object::operator delete (void* p)//
{
    free(p);
}

void* Object::operator new[] (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

bool Object::operator == (const Object& obj)
{
    return (this == &obj);
}
bool Object::operator != (const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{

}

}
