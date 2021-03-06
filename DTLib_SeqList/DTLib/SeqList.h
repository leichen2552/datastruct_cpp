#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class SeqList : public List<T>{
protected:
    T* m_array;
    int m_length;
public:
    bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i<=m_length));

        ret = ret && (m_length < capactity());

        if(ret)
        {
            for(int p=m_length-1; p>=i; p--)
            {
                m_array[p+1] = m_array[p];
            }

            m_array[i] = e;

            m_length++;
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = ((0<=i)&&(i <m_length));
        ret = ret && (m_length < capactity());

        if(ret)
        {
            for(int p=i; p<m_length-1; p++)
            {
                m_array[p] = m_array[p-1];
            }

            m_length--;
        }

        return ret;
    }
    bool set(int i, const T& e)
    {
        bool ret = ((0<=i)&&(i <m_length));

        if(ret)
        {
            m_array[i] = e;
        }

        return ret;
    }
    bool get(int i, T& e)const//通过一个引用来返回目标参数的值，换句话来说，get返回的是当前获取操作是否成功，目标参数的值就通过引用参数来返回，在类的设计中，每个操作都返回当前操作是否成功
    {
        bool ret = ((0<=i)&&(i <m_length));

        if(ret)
        {
            e = m_array[i];
        }

        return ret;
    }
    int length()const
    {
        return m_length;
    }
    void clear()
    {
        m_length = 0;
    }
    //顺序存储线性表的数组访问方式
    T& operator[] (int i)
    {
        if((0<=i) && (i<m_length))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid ...");
        }
    }

    T operator[](int i)const
    {
        return const_cast<SeqList<T>&>(*this)[i];
    }
    //顺序存储空间的容量
    virtual int capactity() const = 0;
}

}

#endif // SEQLIST_H
