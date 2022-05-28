#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinuxLinkQueue.h"
#include "Array.h"
#include "DynamicArray.h"

namespace DTLib {

enum BTNodePos
{
    ANY,  //pos = ANY任意位置，判断位置是不是为空，np->left = n，np->right = n，如果左右字数都有孩子，则插入失败返回false;
    LEFT, //pos = left插入左位置，判断左位置是不是为空，np->left = n
    RIGHT //pos = right插入右位置，判断右位置是不是为空，np->right = n
};

enum BTTraversal
{
    PreOrder,   //先序遍历
    InOrder,    //中序遍历
    PostOrder   //后序遍历
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    LinuxLinkQueue<BTreeNode<T>*> m_queue;

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


    /*删除节点，第一个参数是待删除的节点，第二个参数是返回的子树引用，也就成了被删除子树的根节点*/
    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if(ret == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
        }
        else
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);//创建一个指针指向node的父节点

                if(parent->left == node)//如果父指针的左孩子是该节点
                {
                    parent->left = NULL;//则左孩子为空
                }
                else if(parent->right == node)//如果父指针的右孩子是该节点
                {
                    parent->right = NULL;//则右孩子为空
                }

                node->parent = NULL;//再将该节点的父节点断开，则父子关系彻底断掉
            }

            ret->m_root = node;//最后，将node作为返回值的根节点返回
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            free(node->left);
            free(node->right);

            //std::cout << node->value << std::endl;

            if(node->flag())
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node)const
    {
///一般写法func1
//        int ret = 0;

//        if( node != NULL)
//        {
//            ret = count(node->left) + count(node->right) + 1;
//        }

//        return (ret);

///炫技写法func2
        return (node != NULL) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            int hl = height(node->left);
            int rl = height(node->right);

            ret = ((hl > rl) ? hl : rl) + 1;
        }

        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            BTreeNode<T>* child[] = {node->left, node->right};

            //编程技巧指针操作符取反只有可能是真或者假，node为非空，取一次反就是0，再取一次反就是1，所以ret = 2
            ret = (!!node->left + !!node->right);

            for(int i=0; (i<2) && (ret<2); i++)//如果当前的度数就为2了，那么这个循环将不会被执行
            {
                int d = degree(child[i]);

                if(ret < d)
                {
                    ret = d;
                }
            }

            /*
            ///度数最大值为2
            if(ret < 2)//但凡发现一个节点的度为2，那么就是度2
            {
                int dl = degree(node->left);

                if(ret < dl);
                {
                    ret = dl;
                }
            }
            if(ret < 2)
            {
                int dr = degree(node->right);

                if(ret < dr);
                {
                    ret = dr;
                }
            }
            */

            /*
            int dl = degree(node->left);
            int dr = degree(node->right);

            ret = (!!node->left + !!node->right);

            if(ret < dl)
            {
                ret = dl;
            }

            if(ret < dr)
            {
                ret = dr;
            }*/
        }

        return ret;
    }

    void preOrderTraversal(BTreeNode<T>* node, LinuxLinkQueue<BTreeNode<T>*>& queue)//队列参数保存遍历次序
    {
        if(node != NULL)
        {
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }

    void inOrderTraversal(BTreeNode<T>* node, LinuxLinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            inOrderTraversal(node->left, queue);
            queue.add(node);
            inOrderTraversal(node->right, queue);
        }
    }

    void postOrderTraversal(BTreeNode<T>* node, LinuxLinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

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
        BTree<T>* ret = NULL;
        BTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value...");
        }
        else
        {
            remove(node, ret);//node是指向BTreeNode的指针，所以不需要强制转换

            m_queue.clear();//在删除元素时，为了安全起见也要清空队列
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;///这里再编译的时候出现了错误，起初写的是Tree<T>*，然后根据报错提示无法将Tree<T>* 转换成 BTree<T>*&，因为下面else
                             ///中romove函数中的第二个参数是BTree<T>*&（二叉树指针的引用），所以这里报错是定义的类型不对，无法强制转换。
                             ///改成BTree<T>*&就行

        node = find(node);//先查找该节点是否在该树中

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invaild ...");
        }
        else
        {
            remove( dynamic_cast<BTreeNode<T>*>(node), ret);//node是指向父类的指针，所以需要强制转换

            m_queue.clear();//在删除元素时，为了安全起见也要清空队列
        }

        return ret;
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

        m_queue.clear();//保证安全器件，清空二叉树的时候需要将队列也清空

        this->m_root = NULL;
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            //为了安全起见，先来clear一下，万一上次的遍历还没结束，又调用了一次begin，那怎么办？先clear，保证begin函数被调用，队列里面只有根节点

            m_queue.clear();//这是把队列清空，而不是把树清空，nnd看错了
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);//判断队列长度是否为0，为0表示遍历结束。
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if(ret)
        {
            BTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            if(node->left != NULL)
            {
                m_queue.add(node->left);
            }
            if(node->right != NULL)
            {
                m_queue.add(node->right);
            }
        }

        return ret;
    }

    T current()
    {
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinuxLinkQueue<BTreeNode<T>*> queue;

        switch (order) {
        case PreOrder:
                preOrderTraversal(root(), queue);
            break;
        case InOrder:
                inOrderTraversal(root(), queue);
            break;
        case PostOrder:
                postOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
            break;
        }

        ret = new DynamicArray<T>(queue.length());

        if(ret != NULL)
        {
            for(int i=0; i<ret->length(); i++,queue.remove())
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create return array...");
        }

        return ret;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
