#include <iostream>
#include "LinkStack.h"
#include "LinkQuene.h"


using namespace std;
using namespace DTLib;

template <typename T>
class StackToQuene: public Quene<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;

    void move() const//const成员函数智能调用const成员函数，pop函数并不是const成员函数，所以要把这两个变量声明成mutable对象
    {
        if(m_stack_out.size() == 0)//出栈为空的时候
        {
            while(m_stack_in.size() > 0) //进栈里面有元素
            {
                m_stack_out.push(m_stack_in.top()); //把进栈 栈顶的元素压入 出栈
                m_stack_in.pop();                   //把进栈的元素弹出
            }
        }
    }
public:
    void add(const T& e) //O(1)
    {
        m_stack_in.push(e);//把数据压入进栈当中
    }
    void remove()//O(n)
    {

//        if(m_stack_out.size() == 0)//出栈为空的时候
//        {
//            while(m_stack_in.size() > 0) //进栈里面有元素
//            {
//                m_stack_out.push(m_stack_in.top()); //把进栈 栈顶的元素压入 出栈
//                m_stack_in.pop();                   //把进栈的元素弹出
//            }
//        }

        move();

        if(m_stack_out.size() > 0)                  //判断出栈内是否有元素
        {
            m_stack_out.pop();                      //就把数据弹出，相当于就是出队列
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current quene");
        }
    }
    T front() const//O(n)
    {
//        if(m_stack_out.size() == 0)//出栈为空的时候
//        {
//            while(m_stack_in.size() > 0) //进栈里面有元素
//            {
//                m_stack_out.push(m_stack_in.top()); //把进栈 栈顶的元素压入 出栈
//                m_stack_in.pop();                   //把进栈的元素弹出
//            }
//        }

        move();

        if(m_stack_out.size() > 0)                  //判断出栈内是否有元素
        {
            return m_stack_out.top();               //就返回出栈 栈顶的元素，也就是出队列的元素
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current quene");
        }
    }

    void clear()//O(n)
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }

    int length() const
    {
        return (m_stack_in.size() + m_stack_out.size());
    }
};


int main()
{

    StackToQuene<int> sq;

    for(int i=0; i<10; i++)
    {
        sq.add(i);
    }

    while(sq.length() > 0)
    {
        cout << sq.front() << endl;

        sq.remove();
    }


    return 0;
}
