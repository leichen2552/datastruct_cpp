#include <iostream>
#include "Exception.h"
#include "string.h"
#include "Object.h"
#include "LinkList.h"

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

//abc 有6种
//aac 就只有三种，所以需要处理相同字符

void permutation(char* s, char* e)//e用来最终打印
{
    if(*s == '\0')
    {
        cout << e <<endl;
    }
    else
    {
        int len = strlen(s);
        for(int i=0; i<len; i++)
        {
            if((i==0) || (s[0] != s[i]))
            {
                swap(s[0],s[i]);
                permutation(s+1,e);
                swap(s[0],s[i]);
            }
        }
    }
}

///打印偶数节点
void r_print_even(Node* list)
{
    if(list != NULL)
    {
        r_print_even(list->next);

        if((list->value % 2) == 0)
        {
            cout << list->value << endl;
        }
    }
}

template <int SIZE>
class QueneSolution : public Object
{
protected:
    enum {N = SIZE + 2};//定义边界

    struct Pos:public Object//定义位置结构体
    {
        Pos(int px=0, int py=0) : x(px), y(py) //结构体，初始化列表
        {
        }
        int x;
        int y;
    };

    int m_chessboard[N][N];//定义棋盘
    Pos m_direction[3];//方向数组，检查3个方向上有没有别的皇后
    LinkList<Pos> m_solution;//链表来存储皇后的位置
    int m_count;//记录解决方案

    void init()
    {
        m_count = 0;

        for(int i=0; i<N; i+=(N-1))//初始化边界，边界是2
        {
            for(int j=0; j<N; j++)
            {
                m_chessboard[i][j] = 2;
                m_chessboard[j][i] = 2;
            }
        }

        for(int i=1; i<=SIZE; i++)//初始化棋盘格，每个数据为0
        {
            for(int j=1; j<=SIZE; j++)
            {
                m_chessboard[i][j] = 0;
            }
        }
        //初始化3个方向
        m_direction[0].x = -1;
        m_direction[0].y = -1;

        m_direction[1].x = 0;
        m_direction[1].y = -1;

        m_direction[2].x = 1;
        m_direction[2].y = -1;
    }

    //打印棋盘
    void printChessBoard()
    {
        //遍历链表，打印皇后位置
        for(m_solution.move(0); !m_solution.end(); m_solution.next())
        {
            cout << "(" << m_solution.current().x << "," << m_solution.current().y << ")  ";
        }

        cout << endl;

        //打印棋盘，0代表空，1代表皇后，2代表边界
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                switch(m_chessboard[i][j])
                {
                    case 0: cout << " ";break;
                    case 1: cout << "#";break;
                    case 2: cout << "*";break;
                }
            }

            cout << endl;
        }

        cout << endl;
    }

    //检查三个方向上有没有别的皇后
    bool check(int x, int y, int d)
    {
        bool flag = true;

        do
        {//加上方向数据
            x+=m_direction[d].x;
            y+=m_direction[d].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }
        while(flag);

        return (m_chessboard[x][y] == 2);//边界数据是2，如果到边界上，就证明这个方向上没有皇后了
    }

    void run(int j)//检查第j行有没有能力放置皇后的位置
    {
        if(j <= SIZE)
        {
            for(int i=1; i<=SIZE; i++)
            {
                if(check(i,j,0) && check(i,j,1) && check(i,j,2))//检查当前位置对应的三个方向，如果检查三个方向都没有皇后，那么就可以放置皇后
                {
                    m_chessboard[i][j] = 1;//放置皇后

                    m_solution.insert(Pos(i,j));

                    //上面两行可以放置皇后，判断下一行能不能放皇后，递归调用自己
                    run(j + 1); //如果这个函数返回，那么这个位置不能能放置皇后，产生了回溯，

                    m_chessboard[i][j] = 0;//将我们之前的标记给清空

                    m_solution.remove(m_solution.length() - 1);
                }
            }
        }
        else//表示前八行都放置了皇后，就表明这是一种解决方案
        {
            m_count++;//找到一种解决方案就自加1

            printChessBoard();
        }
    }


public:
    QueneSolution()
    {
        init();
    }
    void run()
    {
        run(1);//从第一行来放置皇后

        cout << "Total: " << m_count << endl;
    }
};

int main()
{
    QueneSolution<4> qs;

    qs.run();

    return 0;
}

