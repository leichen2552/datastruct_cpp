#include <iostream>
#include "GTree.h"

using namespace std;
using namespace DTLib;

int main()
{
    GTree<char> t;
    GTreeNode<char>* node = NULL;

    t.insert('A',NULL);

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

    char* s = "KLFGMIJ";

    for(int i=0; i<7; i++)
    {
        TreeNode<char>* node = t.find(s[i]);

        while( node != NULL)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }

    return 0;
}
