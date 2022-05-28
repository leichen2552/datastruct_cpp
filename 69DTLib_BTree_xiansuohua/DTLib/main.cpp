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

    SharedPointer<Array<int>> tr = bt.traversal(LevelOrder);

    for(int i=0; i<tr->length(); i++)
    {
        cout << (*tr)[i] << " ";
    }

    cout << endl;

    BTreeNode<int>* head = bt.thread(LevelOrder);

    while(head->right != NULL)//先将head移动到链表尾部
    {
        head = head->right;
    }

    while(head != NULL)
    {
        cout << head->value << " ";
        head = head->left;// 反过来输出
    }

//    while(head != NULL)
//    {
//        cout << head->value << " ";
//        head = head->right;
//    }

    cout << endl;

    return 0;
}
