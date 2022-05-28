#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib {

template < typename T, int N >
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;

public:
    StaticStack()
    {
        m_top = -1;//初始化没有所谓的栈顶，所以是-1
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }

    void push(const T& e)
    {
        if(m_size < N)
        {
            m_space[m_top + 1] = e;//即便这里发生了异常，先赋值，栈内部的状态也不能发生改变，为了异常安全
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "No Space in current stack ...");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if(m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size()const
    {
        return m_size;
    }
};

}

#endif // STATICSTACK_H
