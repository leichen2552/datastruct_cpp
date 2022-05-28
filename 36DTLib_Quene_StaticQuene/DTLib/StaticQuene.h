#ifndef STATICQUENE_H
#define STATICQUENE_H

#include "Quene.h"
#include "Exception.h"

namespace DTLib {

template <typename T, int N>
class StaticQuene : public Quene<T>
{
protected:
    T m_space[N];   //队列存储空间
    int m_front;    //队头标识
    int m_rear;     //队尾标识
    int m_length;   //队列的长度
public:
    StaticQuene()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }
    int capacity() const
    {
        return N;
    }
    void add(const T& e)
    {
        if(m_length < N)
        {
            m_space[m_rear] = e;
            m_rear = (m_rear + 1) % N;//循环计数法
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current quene ...");
        }
    }
    void remove()
    {
        if( m_length > 0)
        {
            m_front = (m_front + 1) % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current quene ...");
        }
    }

    T front()const
    {
        if(m_length > 0)
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current quene");
        }
    }

    void clear()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length()const
    {
        return m_length;
    }
};

}

#endif // STATICQUENE_H
