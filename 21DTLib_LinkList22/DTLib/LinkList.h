#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib {

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node:public Object
    {
        T value;
        Node* next;
    };

    //1、头结点里面就有一个value,这是为了解决使用者出现 LinkList<Test> list这样的问题
    //mutable Node m_header;
    //2、所以采用这样子的方式，在构造头结点的时候，没有调用构造函数，只有一个指针，这个数组没有实际的作用，仅仅就是占一份空间
    //避开泛指类型T作为构造函数的调用
    mutable struct : public Object {        //这个类没有像Node一样继承Object这个类，所以会造成内存布局上的不同就会出bug
        char reserved[sizeof(T)];
        Node* next;
    } m_header;

    int m_length;


    Node* position(int i)const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }
public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
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
            Node* node = new Node();

            if(node != NULL)
            {
                Node* current = position(i);

                node->value = e;            //把待插入的数值赋给node节点
                node->next = current->next; //把当前current的next指针是指向下一个元素的，赋给node节点的next指针，让node节点的next指针指向该元素
                current->next = node;       //把current的next指针指向该node节点，保证链表连接起来

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

            Node* todel = current->next;//当前current指针所指向的数据元素就是我们要删除元素
            current->next = todel->next;

            delete todel;

            m_length--;
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

    int length() const
    {
        return m_length;
    }


    void clear()
    {
        while(m_header.next)
        {
            Node* todel = m_header.next;

            m_header.next = todel->next;

            delete todel;
        }

        m_length = 0;
    }

    ~LinkList()
    {
        clear();
    }
};

}



#endif // LINKLIST_H
