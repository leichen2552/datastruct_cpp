#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H


#include "LinkList.h"

namespace DTLib {

template < typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;//采用C语言中暴力的方式对没有用到的参数进行处理
            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];


    Node* create()
    {
        SNode* ret = NULL;

        for(int i=0; i<N; i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;//只是分配的内存，并没有创建对象，所以需要在上面创建SNode并继承Node，然后下面一行创建对象
                ret = new(ret)SNode();//new后面的括号是指在指定的内存空间上创建对象
                m_used[i] = 1;
                break;
            }

        }

        return ret;
    }

    void destroy(Node *pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);//父类指针转换成子类指针，用dynamic_cast

        for(int i=0; i<N; i++)
        {
            if(pn == (space + i))
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }

public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] = 0;
        }
    }
    int capacity()
    {
        return N;
    }

    ~StaticLinkList()
    {
        this->clear();
    }
};

}

#endif // STATICLINKLIST_H
