#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "cstdlib"
#include "Pointer.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref; //计数机制成员指针

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if(this->m_ref)
        {
            (*this->m_ref)++;
        }
    }

public:
    SharedPointer(T* p = NULL) :m_ref(NULL)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));

            if(this->m_ref)
            {
                *(this->m_ref) = 1;//这个空间已经由一个sharedpointer指针对象指定了
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memeory to create SharedPointer object ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj):Pointer<T>(NULL)
    {
        assign(obj);
    }


    SharedPointer<T>& operator= (const SharedPointer<T>& obj)
    {
        if(this != &obj)//既然要赋值，就要把当前对象的属性都置空
        {
            clear();

            assign(obj);
        }

        return *this;
    }
    void clear()
    {
        //先用临时变量接管这个对象
        T* todel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;//当前对象指针置0
        this->m_ref = NULL;//当前对象的计数机制置0


        //此时这个对象对象不再指向这篇堆空间了，计数就要减1，如果计数是0，就要释放这片堆空间
        if(ref)
        {
            (*(ref))--;

            if(*(ref) == 0)
            {
                free(ref);

                delete todel;
            }
        }
    }
    ~SharedPointer()
    {
        clear();
    }
};


template <typename T >
bool operator==(const SharedPointer<T>& l, SharedPointer<T>& r)
{
    return (l.get() == r.get());//const成员函数不能调用非const成员函数
}

template <typename T >
bool operator!=(const SharedPointer<T>& l, SharedPointer<T>& r)
{
    return  !(l == r);//不相等操作符的重载 用 相等操作符的重载来实现
}

}

#endif // SHAREDPOINTER_H
