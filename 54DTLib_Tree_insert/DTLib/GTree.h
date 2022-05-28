#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

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

        if(node != NULL)//判断当前节点是不是空，不可能将一个空节点插入树
        {
            if(this->m_root == NULL)//判断当前的树是不是一棵空树
            {   //如果是空树
                node->parent = NULL;//那么该节点的父节点就是空
                this->m_root = node;//那么该节点就是根节点
            }
            else
            {   //如果不是空树
                GTreeNode<T>* np = find(node->parent);//查找指定是父节点是否存在于这个树中

                if(np != NULL)//如果找到该节点
                {
                    //判断是否插入重复节点，比如已经有个B节点，再次插入B节点就不可以
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);//再创建一个节点，是为了之前find函数已经查找过了，不需要在继续查找

                    //从n节点继续向下查找
                    if(np->child.find(n) < 0)
                    {
                        np->child.insert(n);
                    }


                }
                else//如果找不到该节点，就抛出异常
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invaid parent tree node ...");
                }
            }
        }
        else//如果插入的该节点为空，就抛出一个异常
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node connot be NULL ...");
        }

        return ret;
    }

    //直接简单粗暴的插入新元素，只有线性的数据结构才可以利用下标访问。非线性的数据结构不可用下标定位。因此插入新节点，需要先指定父节点
    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = new GTreeNode<T>();

        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
        }

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
