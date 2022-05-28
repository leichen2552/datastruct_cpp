#ifndef LIST_H
#define LIST_H
#include "Object.h"

namespace DTLib
{

template <typename T>
class List : public Object
{         //这只是一个抽象类
protected:
    List(const List&);
    List& operator=(const List& Ts);//我们自己定义了一个构造函数，那么编译器就不会提供默认的构造函数和拷贝构造函数
                                    //这里是禁用了拷贝构造函数
public:
    List() { }//就需要我们自己提供一个构造函数
    virtual bool insert(const T& e) = 0;//默认往线性表的尾部插入元素
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e)const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};

}


#endif // LIST_H
