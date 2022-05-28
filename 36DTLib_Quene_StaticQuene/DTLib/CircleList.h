#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace DTLib {

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node* last()const//获得最后一个节点的指针
    {
        return this->position(this->m_length-1)->next;
    }

    void last_to_first() const
    {
        last()->next = this->m_header.next;
    }

public:
    bool insert(const T& e)
    {
        return insert(this->m_length,e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;

        i = i % (this->m_length + 1);

        ret = LinkList<T>::insert(i, e);

        if( (ret) && (i == 0) )
        {
            last_to_first();
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        if(i == 0)
        {
            Node* toDel = this->m_header.next;

            if(toDel != NULL)
            {
                this->m_header.next = toDel->next;
                this->m_length--;

                if(this->m_length > 0)
                {
                    last_to_first();

                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }

                this->destroy(toDel);//为了异常安全，最后才来销毁首节点
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));//const 函数里面不允许修改值，mod函数修改了，所以报错
    }

    bool get(int i, const T& e)const
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find(const T& e)const
    {
        int ret = -1;

/////////////////////////////////////////////////////////////////
///在find函数里，我们吧最后一个节点的next指针置空，那么循环链表就成了单链表，
/// 所以在调用父类的find函数就可以，想法很精妙，在找到之后在调用last_to_first函数连接上，就OK。
/// 但是如果find函数出现了异常,就没办法执行到last_to_first(),这个时候循环链表就成了单链表，就失败了
/// 如此分析，就需要重新实现
///        last()->next = NULL;
///
///        ret = LinkList<T>::find(e);
///
///        last_to_first();
////////////////////////////////////////////////////////////////
        Node* slider = this->m_header.next;

        for(int i=0; i<this->m_length; i++)
        {
            if(slider->value == e)
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);
        }

        if(this->m_length == 1)
        {
            Node* todel = this->m_header.next;

            this->m_header.next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(todel);
        }
    }

    bool move(int i, int step)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return  (this->m_length == 0) || (this -> m_current == NULL);
    }



    ~CircleList()
    {
        clear();
    }
};

}


#endif // CIRCLELIST_H
