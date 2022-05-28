#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"

namespace DTLib
{

template <typename T>
class GTree : public Tree<T>
{
protected:
    //基于节点元素的查找
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value)const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)//先找递归出口
            {
                return node;
            }
            else
            {   //遍历当前节点里面的每一棵子树
                for(node->child.move(0);!node->child.end() && (ret == NULL); node->child.next())//把游标定位到链表0位置处
                {
                    ret = find(node->child.current(),value);//递归查找每一棵子树里面查找目标元素的值
                }
            }
        }

        return ret;
    }

    //基于节点的查找
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj)const
    {
        GTreeNode<T>* ret = NULL;

        if( node == obj )
        {
            return node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), obj);//递归查找每一棵子树的节点
                }
            }
        }

        return ret;
    }


public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)//移除元素值
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)//移除某个节点
    {
        return NULL;
    }

    GTreeNode<T>* find(const T& value)const//基于数据元素值的查找
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node)const//基于节点的查找
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast< GTreeNode<T>* >(this->m_root);
    }

    int degree()const
    {
        return 0;
    }

    int count() const
    {
        return 0;
    }

    int height() const
    {
        return 0;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }
};

}





#endif // GTREE_H
