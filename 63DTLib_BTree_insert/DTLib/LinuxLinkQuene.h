#ifndef LINUXLINKQUENE_H
#define LINUXLINKQUENE_H

#include "Quene.h"
#include "LinuxList.h"
#include "Exception.h"

namespace DTLib {

///用Linux内核链表来实现链表队列
/// 并不是说这个文件是linux内核实现队列的方式
template <typename T>
class LinuxLinkQuene : public Quene<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    int m_length;
public:
    LinuxLinkQuene()
    {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
    }

    void add(const T& e)//O(1)
    {
        Node* node = new Node();

        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head,&m_header);

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No memory to add new element ...");
        }
    }

    void remove()   //O(1)
    {
        if(m_length > 0)
        {
            list_head* toDel = m_header.next;

            list_del(toDel);

            m_length--;

            delete list_entry(toDel, Node, head);

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current quene ...");
        }
    }

    T front()const  //O(1)
    {
        if(m_length > 0)
        {
            return list_entry(m_header.next, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current quene ...");
        }
    }

    void clear()//O(n)
    {
        while (m_length > 0)
        {
            remove();
        }
    }

    int length() const
    {
        return m_length;
    }

    ~LinuxLinkQuene()
    {
        clear();
    }
};

}

#endif // LINUXLINKQUENE_H
