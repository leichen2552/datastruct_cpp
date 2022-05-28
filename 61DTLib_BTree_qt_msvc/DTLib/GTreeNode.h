#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace DTLib {

///工厂方法:
/// 1、在GTreeNode中增加保护成员变量
/// 2、将GTreeNode中的operator new 重载为保护成员函数
/// 3、提供工厂方法GTreeNode<T>* NewNode()
/// 4、在工厂方法中new新节点并将m_flag设置为true

template <typename T >
class GTreeNode : public TreeNode<T>
{
//protected:
//    bool m_flag;///1、在TreeNode中增加保护成员变量

//    /*这是避免两棵树之间的复制*/
//    TreeNode(const TreeNode<T>&);//拷贝构造函数保护
//    TreeNode<T>& operator= (const TreeNode<T>&);//赋值函数

//    /// 2、将TreeNode中的operator new 重载为保护成员函数
//    void* operator new(unsigned int size) throw()//在外部就不能使用new来创建
//    {
//        return Object::operator new(size);
//    }

public:
    LinkList< GTreeNode<T>* > child;

//    GTreeNode()
//    {
//        m_flag = false;
//    }

//    bool flag()
//    {
//        return m_flag;
//    }

    /* 前两步放在了抽象类里面 */
    /// 3、提供工厂方法GTreeNode<T>* NewNode()
    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;/// 4、在工厂方法中new新节点并将m_flag设置为true
        }

        return ret;
    }

};

}


#endif // GTREENODE_H
