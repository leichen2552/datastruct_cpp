#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

///工厂方法:
/// 1、在TreeNode中增加保护成员变量
/// 2、将TreeNode中的operator new 重载为保护成员函数
/// 3、提供工厂方法TreeNode<T>* NewNode()
/// 4、在工厂方法中new新节点并将m_flag设置为true

namespace DTLib {

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;///1、在TreeNode中增加保护成员变量

    TreeNode(const TreeNode<T>&);//拷贝构造函数保护
    TreeNode<T>& operator= (const TreeNode<T>&);//赋值函数

    /// 2、将TreeNode中的operator new 重载为保护成员函数
    void* operator new(size_t size) throw()//在外部就不能使用new来创建
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}


#endif // TREENODE_H
