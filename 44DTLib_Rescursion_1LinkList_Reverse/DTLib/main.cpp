#include <iostream>
#include "Exception.h"

using namespace std;
using namespace DTLib;

struct Node
{
    int value;
    Node* next;
};

Node* create_list(int v, int len)
{
    Node* ret = NULL;
    Node* slider = NULL;

    for(int i=0; i<len; i++)
    {
        Node* n = new Node();

        n->value = v++;
        n->next = NULL;

        if(slider == NULL)
        {
            slider = n;
            ret = n;
        }
        else
        {
            slider->next = n;
            slider = n;
        }
    }

    return ret;
}

void destroy_list(Node* list)
{
    while(list)
    {
        Node* del = list;

        list = list->next;

        delete del;
    }
}

void print_list(Node* list)
{
    while(list)
    {
        cout << list->value << "->";

        list = list->next;
    }

    cout << "NULL" << endl;
}

Node* reverse(Node* list)//用递归方式
{
    if(list == NULL || (list->next == NULL))//如果链表的长度小于2
    {
        return list;                        ///递归先找出口
    }
    else                                    ///再找核心的小问题
    {
        Node* guard = list->next;           //设置一个指针指向当前链表的第二个节点
        Node* ret = reverse(list->next);    //递归地调用自己

        guard->next = list;                 //guard指针的Next指针指向头结点
        list->next = NULL;                  //头结点的指针指向NULL

        return ret;
    }
}

int main()
{
    Node* list = create_list(1,5);

    print_list(list);

    list = reverse(list);
    print_list(list);

    destroy_list(list);

    return 0;
}

