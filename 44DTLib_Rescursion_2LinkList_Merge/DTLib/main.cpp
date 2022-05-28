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

Node* Merge(Node* list1, Node* list2)
{
    if(list1 == NULL)                   ///出口
    {
        return list2;
    }
    else if(list2 == NULL)              ///出口
    {
        return list1;
    }
    else if(list1->value < list2->value)    ///如果链表1的第一个元素比链表2的第一个元素小
    {
//        Node* list1_ = list1->next;         ///先把链表1的第一个节点拿出来，剩下的字表有事一个新的链表
//        Node* list = Merge(list1_,list2);   ///把这个新的链表和链表2再合并

//        list1->next  = list;                ///然后将第一个节点指向合并好的list

//        return list1;

        return (list1->next = Merge(list1->next,list2), list1);//用更简洁的语句，逗号表达式的值就是最后一个值表达式的值
    }
    else
    {
//        Node* list2_ = list2->next;
//        Node* list = Merge(list1,list2_);

//        list2->next = list;

//        return list2;

        return (list2->next = Merge(list2->next,list1), list2);
    }
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

void HanoiTower(int n, char a, char b, char c)//    a==>src     b==> middle     c ==> dest
{
    if(n == 1)
    {
        cout << a << "-->" << c << endl;
    }
    else
    {
        HanoiTower(n-1, a, c, b);
        HanoiTower(1, a, b, c);
        HanoiTower(n-1, b, a, c);
    }
}

int main()
{
    HanoiTower(4, 'a', 'b', 'c');

    return 0;
}

