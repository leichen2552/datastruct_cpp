#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "LinuxList.h"
#include "DualLinkList.h"

namespace DTLib {

template <typename T >
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);//直接转换就会造成编译错误

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }
public:
    DualCircleList()
    {
        this->m_length = 0;
        this->m_step = 1;

        m_current = NULL;

        INIT_LIST_HEAD(&m_header);
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;

        Node* node = new Node();

        i = i % (this->m_length + 1);

        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head, position(i)->next);

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to insert new element ... ");
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) &&(i < this->m_length));

        if(ret)
        {
            list_head* todel = position(i)->next;

            if(m_current == todel)
            {
                m_current = todel->next;
            }

            list_del(todel);

            this->m_length--;

            delete list_entry(todel, Node, head);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = true;

        i = mod(i);

        ret = ( (0<=i) && (i < this->m_length));

        if(ret)
        {
//            Node* current = position(i);
//            current->next->value = e;
            list_entry(position(i)->next, Node, head)->value = e;
        }

        return ret;
    }

    T get(int i)const
    {
        T ret;

        if( get(i, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
        }

        return ret;
    }

    bool get(int i, T& e)const
    {
        bool ret = true;

        i = mod(i);

        ret = ( (0<=i) && (i < this->m_length));

        if(ret)
        {
//            Node* current = position(i);
//            e = current->next->value;
            //进一步优化
            e = list_entry(position(i)->next, Node, head)->value;
        }

        return ret;
    }

    int find(const T& e)const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;

        list_for_each(slider,&m_header)
        {
            if( list_entry(slider, Node, head)->value == e )
            {
                ret = i;
                break;
            }
            i++;
        }

        return ret;
    }

    int length()const
    {
        return this->m_length;
    }

    void clear()
    {
        while(this->m_length > 0)
        {
            remove(0);
        }
    }

    bool move(int i, int step = 1)
    {
        bool ret = (step > 0);

        i = mod(i);

        ret = ret && ((0<=i) && (1 < this->m_length));

        if(ret)
        {
            m_current = position(i)->next;

            this->m_step = step;
        }

        return ret;
    }

    bool end()
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    T current()
    {
        if( !end())
        {
            return  list_entry(m_current, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value at current position ...");
        }
    }

    bool next()
    {
        int i = 0;

        while( (i < this->m_step) && !end() )
        {
            //我们的双向循环链表和Linux的双向循环链表不一样，Linux的双向循环链表包含头结点，我们的不包含，
            //所以我们的需要判断是不是头结点，是的话就需要调过

            if(m_current != &m_header)  //判断是不是头结点，是的话就指向下一个
            {
                m_current = m_current->next;//挪动位置
                i++;
            }
            else//如果不是，就什么也不做
            {
                m_current = m_current->next;
            }
        }
        if(m_current == &m_header)//while结束之后，判断是不是又指向了头结点，是的话，指向下一个
        {
            m_current = m_current->next;
        }

        return  (i == this->m_step);
    }

    virtual bool pre()
    {
        int i = 0;

        while( (i < this->m_step) && !end() )
        {
            //我们的双向循环链表和Linux的双向循环链表不一样，Linux的双向循环链表包含头结点，我们的不包含，
            //所以我们的需要判断是不是头结点，是的话就需要调过

            if(m_current != &m_header)  //判断是不是头结点，是的话就指向下一个
            {
                m_current = m_current->prev;//挪动位置
                i++;                        //然后计数
            }
            else//如果是头结点，直接跳过
            {
                m_current = m_current->prev;
            }
        }
        if(m_current == &m_header)//while结束之后，判断是不是又指向了头结点，是的话跳过去，指向下一个
        {
            m_current = m_current->prev;
        }

        return  (i == this->m_step);
    }

    ~DualCircleList()
    {
        clear();
    }
};


}

#endif // DUALCIRCLELIST_H
