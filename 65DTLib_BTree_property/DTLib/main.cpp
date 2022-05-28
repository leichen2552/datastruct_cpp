#include <iostream>
#include "BTree.h"

using namespace std;
using namespace DTLib;

int main()
{
    BTree<int> bt;
    BTreeNode<int>* n = NULL;

    bt.insert(1,n);

    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);

    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10, n, LEFT);

    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);

    cout << bt.count() << endl;

    cout << bt.height() << endl;

    cout << bt.degree() << endl;

    int a[] = {8, 9, 10, 11, 7};//用类似单链表遍历的方式从叶子结点访问到根节点
    SharedPointer< Tree<int> > sp = bt.remove(3);

    for(int i=0; i<5; i++)
    {
        TreeNode<int>* node = bt.find(a[i]);
        //TreeNode<int>* node = sp->find(a[i]);

        while (node)
        {
            //cout << node->value << " ";
            node = node->parent;
        }

        //cout << endl;
    }

    return 0;
}
