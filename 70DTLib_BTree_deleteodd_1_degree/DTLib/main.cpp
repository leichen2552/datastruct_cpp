#include <iostream>
#include "BTree.h"

using namespace std;
using namespace DTLib;

template < typename T >
BTreeNode<T>* createTree()
{
    static BTreeNode<int> ns[9];

    for(int i=0; i<9; i++)
    {
        ns[i].value = i;
        ns[i].parent = NULL;
        ns[i].left = NULL;
        ns[i].right = NULL;
    }

    ns[0].left = &ns[1];
    ns[0].right = &ns[2];
    ns[1].parent = &ns[0];
    ns[2].parent = &ns[0];

    ns[1].left = &ns[3];
    ns[1].right = NULL;
    ns[3].parent = &ns[1];

    ns[2].left = &ns[4];
    ns[2].right = &ns[5];
    ns[4].parent = &ns[2];
    ns[5].parent = &ns[2];

    ns[3].left = NULL;
    ns[3].right = &ns[6];
    ns[6].parent = &ns[3];

    ns[4].left = &ns[7];
    ns[4].right = NULL;
    ns[7].parent = &ns[4];

    ns[5].left = &ns[8];
    ns[5].right = NULL;
    ns[8].parent = &ns[5];

    return ns;
}

template < typename T >
void printInOrder(BTreeNode<T>* node)
{
    if( node != NULL )
    {
        printInOrder(node->left);

        cout << node->value <<" ";

        printInOrder(node->right);
    }
}

template < typename T >
void printDualList(BTreeNode<T>* node)
{
    BTreeNode<T>* g = node;

    cout << "head -> tail: " << endl;

    while( node != NULL )
    {
        cout << node->value << " ";

        g = node;

        node = node->right;
    }

    cout << endl;

    cout << "tail -> head: " << endl;

    while( g != NULL )
    {
        cout << g->value << " ";

        g = g->left;
    }

    cout << endl;
}

///包含根节点为单度的情况
template < typename T >
BTreeNode<T>* delOdd1(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = NULL;

    if(node != NULL)//定义递归出口
    {
        //判断度为1的情况
        if( ((node->left != NULL) && (node->right == NULL)) ||
            ((node->left == NULL) && (node->right != NULL)) )
        {
            //定义父节点指针并初始化为node节点的父节点，这里需要强制类型转换
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            //定义节点孩子指针，并用三目运算符判断到底是左节点还是右节点
            BTreeNode<T>* node_child = (node->left != NULL) ? node->left : node->right;

            //判断父节点是否为空，有可能这个树的根节点就是单度的，但是根节点的父节点为空，因此这里需要判断
            if(parent != NULL)
            {
                //如何描述伪码中parent->child这个节点，
                //但不确定是左孩子还是右孩子，采用指针的引用的类型，三目运算符的方式
                BTreeNode<T>*& parent_child = (parent->left == node) ? parent->left : parent->right;

                //将node孩子指针指向node父节点的孩子，相当于断开的node，连接node父节点与node孩子
                parent_child = node_child;
                node_child->parent = parent;//指定父子关系，将node孩子节点指向父节点

            }
            else
            {
                node_child->parent = NULL;//如果是根节点为单度，那么node_child就为新的根节点
            }

            if(node->flag())//如果该节点是在堆空间中创建的，需要在手动释放
            {
                delete node;
            }

            ret = delOdd1(node_child);//递归的删除单度节点
        }
        else//度为0或者度为2
        {
            delOdd1(node->left);
            delOdd1(node->right);

            ret = node;
        }
    }

    return ret;
}

template < typename T >
void delOdd2(BTreeNode<T>*& node)//参数node为节点指针的引用
{
    if(node != NULL)
    {
        //判断度为1的情况
        if( ((node->left != NULL) && (node->right == NULL)) ||
            ((node->left == NULL) && (node->right != NULL)) )
        {
            //定义节点孩子指针，并用三目运算符判断到底是左节点还是右节点
            BTreeNode<T>* node_child = (node->left != NULL) ? node->left : node->right;

            if(node->flag())
            {
                delete node;
            }

            node = node_child;//重新指定孩子节点，但是node是一个引用，是该节点左孩子还是右孩子的引用

            delOdd2(node);

        }
        else//度为0或者度为2
        {
            delOdd2(node->left);
            delOdd2(node->right);
        }
    }
}


///中序线索化
template <typename T>
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& pre)
{
    //在中序遍历的时候，使用指针连接
    if(node != NULL)
    {
        //中序遍历左子树
        inOrderThread(node->left, pre);

        //node的左指针，也就是前向指针指向pre节点
        node->left = pre;

        //考虑pre节点不为空情况
        if(pre != NULL)
        {
            pre->right = node;//pre的后向节点指向node
        }

        pre = node;//移动node指针，将node赋值给pre

        inOrderThread(node->right, pre);//中序遍历右子树
    }
}


template <typename T>
BTreeNode<T>* inOrderThread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre = NULL;

    inOrderThread(node, pre);//中序线索化

    while( (node != NULL) && (node->left != NULL))//找到头结点
    {
        node = node->left;
    }

    return node;

}

///中序线索化2
template <typename T>
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& head,BTreeNode<T>*& tail)
{
    if(node != NULL)//递归出口
    {
        BTreeNode<T>* h = NULL;
        BTreeNode<T>* t = NULL;

        inOrderThread(node->left, h, t);//中序遍历左子树

        node->left = t;

        if(t != NULL)
        {
            t->right = node;
        }

        head = ((h != NULL) ? h : node);//确定头结点

        h = NULL;
        t = NULL;

        inOrderThread(node->right, h, t);

        node->right = h;

        if(h != NULL)
        {
            h->left = node;
        }

        tail = ((t != NULL) ? t : node);//确定尾结点

    }
}

template <typename T>
BTreeNode<T>* inOrderThread2(BTreeNode<T>* node)
{
    BTreeNode<T>* head = NULL;
    BTreeNode<T>* tail = NULL;

    inOrderThread(node, head, tail);//中序线索化

    return head;
}


int main()
{
    BTreeNode<int>* ns = createTree<int>();

    printInOrder(ns);

    cout << endl;

//    delOdd2(ns);

//    printInOrder(ns);

//    cout << endl;

    ns = inOrderThread2(ns);

    printDualList(ns);

    return 0;
}
