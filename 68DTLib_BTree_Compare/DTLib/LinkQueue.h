#ifndef LINKQUENE_H
#define LINKQUENE_H

#include "Quene.h"
#include "LinkList.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class LinkQuene : public Quene<T>
{
protected:
    LinkList<T> m_list;
public:
    void add(const T& e)//O(n)
    {
        m_list.insert(e);
    }

    void remove()
    {
        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current quene ...");
        }
    }

    T front()const
    {
        if(m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current quene ...");
        }
    }

    void clear()//O(n)
    {
        m_list.clear();
    }

    int length() const
    {
        return m_list.length();
    }
};

}

#endif // LINKQUENE_H
