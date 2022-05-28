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


    SharedPointer< BTree<int> > btClone = bt.clone();

    BTree<int> nbt;

    nbt.insert(0, NULL);

    n = nbt.find(0);
    nbt.insert(6, n, LEFT);
    nbt.insert(2, n, RIGHT);

    n = nbt.find(2);
    nbt.insert(7, n, LEFT);
    nbt.insert(8, n, RIGHT);

    SharedPointer< BTree<int> > r = bt.add(nbt);

    int a[] = {8, 9, 10, 13, 15};//用类似单链表遍历的方式从叶子结点访问到根节点

    cout << "old Tree : "<< endl;
    for(int i=0; i<5; i++)
    {
        TreeNode<int>* node = r->find(a[i]);

        while (node)
        {
            cout << node->value << " ";
            node = node->parent;
        }

        cout << endl;
    }

    SharedPointer<Array<int>> tr = r->traversal(PreOrder);

    for(int i=0; i<tr->length(); i++)
    {
        cout << (*tr)[i] << " ";
    }

    return 0;
}
