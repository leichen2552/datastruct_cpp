#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DTLib {

template <typename T>
class BTreeNode : public TreeNode<T>
{
    ///包含四个公有成员
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    //工厂模式：在实现通用树时，由于节点释放的位置问题，采用工厂模式，在节点申请是打一个标签

    /// 3、提供工厂方法TreeNode<T>* NewNode()
    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;/// 4、在工厂方法中new新节点并将m_flag设置为true
        }

        return ret;
    }
};

}


#endif // BTREENODE_H
