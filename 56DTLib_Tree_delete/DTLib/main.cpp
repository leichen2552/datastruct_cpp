#include <iostream>
#include "GTree.h"

using namespace std;
using namespace DTLib;

int main()
{
    GTree<char> t;
    GTreeNode<char>* node = NULL;
    GTreeNode<char> root;//这个对象是在栈上定义的，但是在clear()函数里面delete函数释放的是堆中的节点。因为这个程序比较短小，运行完就结束了。
                        //可见的问题没有一下子表现出来导致程序发生bug，只有堆中的对象才需要被释放或者说被delete，不是堆中的对象，其生命周期
                        //不需要我们去管理

    root.value = 'A';
    root.parent = NULL;

    t.insert(&root);

    node = t.find('A');
    t.insert('B',node);
    t.insert('C',node);
    t.insert('D',node);

    node = t.find('B');
    t.insert('E',node);
    t.insert('F',node);

    node = t.find('E');
    t.insert('K',node);
    t.insert('L',node);

    node = t.find('C');
    t.insert('G',node);

    node = t.find('D');
    t.insert('H',node);
    t.insert('I',node);
    t.insert('J',node);

    node = t.find('H');
    t.insert('M',node);

    //test1
    //t.remove('D');

    //test2
//    t.remove(t.find('D'));

//    const char* s = "KLFGMIJ";

//    for(int i=0; i<7; i++)
//    {
//        TreeNode<char>* node = t.find(s[i]);

//        while( node != NULL)
//        {
//            cout << node->value << " ";

//            node = node->parent;
//        }

//        cout << endl;
//    }

    //test3
    SharedPointer< Tree<char> > p = t.remove(t.find('D'));

    const char* s = "KLFGMIJ";

    for(int i=0; i<7; i++)
    {
        TreeNode<char>* node = p->find(s[i]);

        while( node != NULL)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }

    return 0;
}


