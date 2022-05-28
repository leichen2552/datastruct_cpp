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

    void free( GTreeNode<T>* node )
    {
        if(node != NULL)
        {
            for(node->child.move(0);!node->child.end();node->child.next())
            {
                free(node->child.current());
            }

            if(node->flag())
            {
                delete node;
            }

            //delete node;//这个对象是在栈上定义的，但是在clear()函数里面delete函数释放的是堆中的节点。因为这个程序比较短小，运行完就结束了。
            //可见的问题没有一下子表现出来导致程序发生bug，只有堆中的对象才需要被释放或者说被delete，不是堆中的对象，其生命周期不需要我们去管理
            //所以这里不能简单粗暴的delete，如果这个对象来源于栈上、全局数据区，所以这里delete node这行代码这样写是不行的
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)//第一个参数是要删除的节点，第二个参数，返回的是一个引用，一个GTree<T>指针的引用
    {
        ret = new GTree<T>();

        if(ret == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
        else
        {
            if(root() == node)//判断当前要删除的节点是不是根节点
            {
                this->m_root = NULL;//如果是那就简单了，直接把根节点指向空就行
            }
            else
            {
                //定义一个别名，是node的父节点中的孩子列表的别名
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                child.remove(child.find(node));//先找到这个节点，然后移除

                node->parent = NULL;//移除之后，该节点的父节点指向空
            }

            ret->m_root = node;//然后把这个节点保存在堆中申请的ret上
        }
    }

    int count(GTreeNode<T>* node)const
    {
        int ret = 0;

        //这里隐藏了if(node == NULL) 就直接返回0作为递归的出口，没有直接明写出来
        if(node != NULL)
        {
            //这里ret = 1,隐藏了if(node->child.length == 0)的情况，就直接返回1作为递归的出口，没有直接明写出来
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node)const
    {
        int ret = 0;

        //这里隐藏了if(node == NULL) 就直接返回0作为递归的出口，没有直接明写出来
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int h = height(node->child.current());

                if(ret < h)
                {
                    ret = h;
                }
            }

            ret += 1;//这里ret = 1,隐藏了if(node->child.length == 0)的情况，就直接返回1作为递归的出口，没有直接明写出来
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        //这里隐藏了if(node == NULL) 就直接返回0作为递归的出口，没有直接明写出来
        if(node != NULL)
        {
            ret = node->child.length();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int d = degree(node->child.current());

                if(ret < d)
                {
                    ret = d;
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
        GTreeNode<T>* node = GTreeNode<T>::NewNode();

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
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the code via parameter value ...");
        }
        else
        {
            remove(node, ret);
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)//移除某个节点
    {
        GTree<T>* ret = NULL;
        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }
        else
        {
            remove( dynamic_cast<GTreeNode<T>*>(node), ret);
        }

        return ret;
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
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }
};

}





#endif // GTREE_H
