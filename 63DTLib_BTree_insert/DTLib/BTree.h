﻿#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinuxLinkQuene.h"

namespace DTLib {

enum BTNodePos
{
    ANY,  //pos = ANY任意位置，判断位置是不是为空，np->left = n，np->right = n，如果左右字数都有孩子，则插入失败返回false;
    LEFT, //pos = left插入左位置，判断左位置是不是为空，np->left = n
    RIGHT //pos = right插入右位置，判断右位置是不是为空，np->right = n
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    /* 基于数据元素查找节点 */
    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const//第一个参数二叉树的根节点的地址，第二个参数是元素值
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                if(ret == NULL)
                {
                    ret = find(node->left, value);
                }

                if(ret == NULL)
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    /* 基于节点查找节点 */
    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const//第一个参数二叉树的根节点的地址，第二个参数是需要查找的目标节点
    {
        BTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            ret = node;
        }
        else
        {
            if(node != NULL)
            {
                if(ret == NULL)
                {
                    ret = find(node->left, obj);
                }

                if(ret == NULL)
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    /*插入新节点*/
    /*第一个参数新节点、第二个参数目标父节点、第三个参数位置参数，连起来读就是把新节点当做目标父节点的孩子插入，pos这个参数为我们指明了目标位置*/
    virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;

        if(pos == ANY)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                return ret;
            }
        }
        else if(pos == LEFT)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == RIGHT)
        {
            if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    /*插入新数据元素*/

public:
    bool insert(TreeNode<T>* node)//插入对位置没有要求的节点
    {
        return insert(node, ANY);
    }

    /*插入新节点*/
    virtual bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        int ret = true;

        if(node != NULL)//如果node不为空
        {
            if(this->m_root == NULL)//如果当前的树是不是一棵空树
            {
                node->parent = NULL;//把当前节点的父指针设为空
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);//查看目标父节点在不在当前的树中

                if(np != NULL)
                {
                    ret = insert( dynamic_cast<BTreeNode<T>*>(node), np, pos);//需要把指向父类的指针强制转换成子类的指针
                }
                else//不在当前树中
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        }
        else//如果node为空，抛出参数异常
        {
            THROW_EXCEPTION(InvalidParameterException, "Paramrter node can be NULL");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        int ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if(node == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
        }
        else
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if(!ret)
            {
                delete node;
            }
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
    }

    BTreeNode<T>* find(const T& value)const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node)const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));//这列需要强制类型的转换，将父类指针转换成子类指针
    }

    BTreeNode<T>* root()const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return NULL;
    }

    int count() const
    {
        return NULL;
    }

    int height() const
    {
        return NULL;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
