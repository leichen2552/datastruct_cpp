#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace DTLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {
        //m_pointer = p;
    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator= (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* p = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete p;
        }

        return *this;
    }



    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};


}

#endif // SMARTPOINTER_H
