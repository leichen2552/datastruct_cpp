#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

//C++原生数组是不允许对象间的复制

namespace DTLib {

template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, const T& e)
    {
        bool ret = ((0<=i) && (i < length()));

        if( ret )
        {
            m_array[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e)const
    {
        bool ret = ((0 <= i) && i<length());

        if(ret)
        {
            e = m_array[i];
        }

        return ret;
    }

    T& operator[] (int i)
    {
        if((0 <= i) && i<length())
        {
            return m_array[i];
        }
        else
        {
            //弥补C++中原生数组的无法检测下标越界
            THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid ...");
        }
    }

    T operator [](int i) const
    {
        //将当前对象的const属性剔除掉
        return (const_cast<Array<T>>(*this)[i]);
    }

    //Array() {}

    T* array() const
    {
        return m_array;//返回原生数组的首地址
    }

    virtual int length() const = 0;//设置成纯虚函数，意味着这个Array类是个抽象的父类，用来被继承，
                                    //Length的实现是在子类当中完成的，这也就是为什么m_array是被保护的
};

}

#endif // ARRAY_H
