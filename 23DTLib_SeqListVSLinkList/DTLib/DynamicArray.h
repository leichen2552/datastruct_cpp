#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* array, int len, int newlen)//O(n)
    {
        T* ret = new T[newlen];

        if(ret != NULL)
        {
            int size = (len < newlen) ? len : newlen;

            for(int i=0; i<size; i++)
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int length)//O(1)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = length;

            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to update DynamicArray object ...");
        }
    }

    void init(T* array, int length)//O(1)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create DynamicArray object ...");
        }
    }
public:
    DynamicArray(int length)//O(1)
    {
        init(new T[length], length);


//            //第一次写法//
//        this->m_array = new T[length];

//        if(this->m_array != NULL)
//        {
//            this->m_length = length;
//        }
//        else
//        {
//            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create DynamicArray object ...");
//        }
    }

    //拷贝构造函数
    DynamicArray(const DynamicArray<T>& obj)
    {
//            //第三次写法，局部变量也可以省掉//
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
//            //第二次写法//
//        T* array = copy(obj.m_array, obj.m_length, obj.m_length);

//        init(array, obj.m_length);

//            //第一次写法//
//        this->m_array = new T[obj.m_length];

//        if(this->m_array != NULL)
//        {
//            this->m_length = obj.m_length;

//            for(int i=0; i<obj.m_length; i++)
//            {
//                this->m_array[i] = obj.m_array[i];
//            }
//        }
//        else
//        {
//            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create DynamicArray object ...");
//        }
    }

    //赋值操作符重载函数
    DynamicArray<T>& operator= (const DynamicArray<T>& obj)//O(n)
    {
        if(this != &obj)
        {
//            //第三次写法，局部变量都可以省掉//
            update(copy(obj.m_array, obj.m_length,obj.m_length), obj.m_length);

//            //第二次写法//
//            T* array = copy(obj.m_array, obj.m_length,obj.m_length);

//            update(array, obj.m_length);

//            //第一次写法//
//            T* array = new T[obj.m_length];

//            if(array != NULL)
//            {
//                for(int i=0; i<obj.m_length; i++)
//                {
//                    array[i] = obj.m_array[i];
//                }

//                T* temp = this->m_array;//保存this指针之前指向的堆空间，用于后面释放

//                this->m_array = array;//把新申请到的空间挂接到this指针上，之前this指针指向的空间就可以将它释放掉
//                this->m_length = obj.m_length;//保存长度信息

//                delete[] temp;
//            }
//            else
//            {
//                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to copy object ...");
//            }
        }

        return *this;
    }

    int length() const//O(1)
    {
        return m_length;
    }

    void resize(int length)//动态重置数组长度//O(n)
    {
        if( length != m_length )
        {
            update(copy(this->m_array, m_length, length), length);
//            //第二次写法//
//            T* array = copy(this->m_array, m_length, length);

//            update(array, length);

//            //第一次写法//
//            T* array = new T[length];//先申请一片堆空间

//            if(array != NULL)
//            {
//                int size = (length < m_length) ? length : m_length;//先取出两个值中较小的那个

//                for(int i=0; i< size ; i++)
//                {
//                    array[i] = this->m_array[i];
//                }

//                //为了异常安全，保存this指针之前指向的堆空间，用于后面释放
//                T* temp = this->m_array;

//                //把新申请到的空间挂接到this指针上，之前this指针指向的空间就可以将它释放掉
//                this->m_array = array;

//                //保存长度信息
//                this->m_length = length;

//                delete[] temp;//再来释放之前this指向的堆空间
//            }
//            else
//            {
//                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to resize object ...");
//            }
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
