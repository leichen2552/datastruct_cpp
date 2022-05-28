#include <iostream>
#include "DualCircleList.h"

using namespace std;
using namespace DTLib;

struct Node : public Object
{
    list_head head;
    int value;
};

int main()
{
    Node node;
    list_head* ld = &node.head;

    Node* pn1 = reinterpret_cast<Node*>(ld);
    Node* pn2 = list_entry(ld, Node, head);

    cout << "pn1 = " << pn1 << endl;
    cout << "pn2 = " << pn2 << endl;

    return 0;
}
