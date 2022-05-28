#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    }m_header;
    int m_length;

    int m_step;//用来保存每次游标移动的数目
    Node* m_current;//游标，用来遍历链表


    Node* position(int i)const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    bool insert(const T& e) //默认往线性表的尾部插入元素
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = ( (0<=i) && (i <= m_length));

        if(ret)
        {
            Node* node = create();//这里的调用create函数取决于是LinkList对象还是StaticLinkList对象

            if(node != NULL)
            {
                Node* current = position(i);
                Node* next = current->next;//这是待插入节点的后继节点

                node->value = e;            //把待插入的数值赋给node节点

                node->next = next;          //1、把node的next指针指向后继节点
                current->next = node;       //2、把current的next指针指向node节点

                //3、判断current是不是头结点，是的话就把node节点的pre置空，不是的话就指向前驱结点
                if(current != reinterpret_cast<Node*>(&m_header))
                {
                    node->pre = current;
                }
                else
                {
                    node->pre = NULL;
                }

                if(next != NULL)//4、判断next节点是不是空
                {
                    next->pre = node;
                }


                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No menory to insert new element ... ");
            }
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = ( (0<=i) && (i < m_length));

        if(ret)
        {
            Node* current = position(i);
            Node* todel = current->next;//当前current的Next指针所指向的数据元素就是我们要删除元素
            Node* next = todel->next;   //标记 待删除节点的下一个节点

            if(m_current == todel)//游标和待删除的节点是什么关系
            {
                m_current = next;
            }

            current->next = next;//1、current的next节点指向待删除节点的下一个节点


            if(next != NULL)//2、如果待删除节点的下一个节点不为空，其实就是判断是不是尾结点
            {
                next->pre = todel->pre;//把待删除节点的前驱赋值给下一个节点的前驱，保证链表接上
            }

            m_length--;//1、先长度减减

            destroy( todel);//2、再摧毁对象，才足够安全
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ( (0<=i) && (i < m_length));

        if(ret)
        {
//            Node* current = position(i);
//            current->next->value = e;
            position(i)->next->value = e;
        }

        return ret;
    }

    virtual T get(int i)const
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
        bool ret = ( (0<=i) && (i < m_length));

        if(ret)
        {
//            Node* current = position(i);
//            e = current->next->value;
            //进一步优化
            e = position(i)->next->value;
        }

        return ret;
    }

    int find(const T& e)const
    {
        int ret = -1;
        int i=0;
        Node* node = m_header.next;

        //while (node)
        while(node)
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

    int length() const
    {
        return m_length;
    }


    void clear()
    {
        while(m_length > 0)
        {
            remove(0);
        }

        m_length = 0;
    }

    //遍历的四个函数
    virtual bool move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);//检测参数是否合法

        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    virtual bool end()
    {
        return (m_current == NULL);
    }

    virtual T current()
    {
        if( !end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value at current position ...");
        }
    }

    virtual bool next()
    {
        int i = 0;

        while( (i < m_step) && !end() )
        {
            m_current = m_current->next;
            i++;
        }

        return  (i == m_step);
    }

    virtual bool pre()
    {
        int i = 0;

        while( (i < m_step) && !end() )
        {
            m_current = m_current->pre;
            i++;
        }

        return  (i == m_step);
    }

    ~DualLinkList()
    {
        clear();
    }
};

}

#endif // DUALLINKLIST_H
