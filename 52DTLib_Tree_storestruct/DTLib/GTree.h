#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"

namespace DTLib
{

template <typename T>
class GTree : public Tree<T>
{
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

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
    }

    GTreeNode<T>* find(const T& value)const
    {
        return NULL;
    }

    GTreeNode<T>* find(TreeNode<T>* node)const
    {
        return NULL;
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
