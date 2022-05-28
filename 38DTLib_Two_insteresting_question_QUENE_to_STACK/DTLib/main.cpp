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

template <typename T>
class QueneToStack: public Stack<T>
{
protected:
    LinkQuene<T> m_quene_in;
    LinkQuene<T> m_quene_out;
    LinkQuene<T>* m_pIn;
    LinkQuene<T>* m_pOut;

    void move()const
    {
        int n = m_pIn->length() - 1;

        for(int i=0; i<n; i++)
        {
            m_pOut->add(m_pIn->front());//把前m_pIn的n-1个元素都移到m_pOut里面去
            m_pIn->remove();            //移进去一个就移除一个
        }
    }

    void swap()
    {
        LinkQuene<T>* temp = NULL;

        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }
public:
    QueneToStack()
    {
        m_pIn = &m_quene_in;
        m_pOut = &m_quene_out;
    }

    void push(const T& e)   //O(1)
    {
        m_pIn->add(e);
    }
    void pop()              //O(n)
    {
        if(m_pIn->length() > 0)
        {
            move();//先把m_pIn的前n-1个元素移入m_pOut

            m_pIn->remove();//再把m_pIn最后的那个元素弹栈

            swap();//然后在交换进队列和出队列的角色
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current quene");
        }
    }
    T top()const        //O(n)
    {
        if(m_pIn->length() > 0)
        {
            move();//先把m_pIn的前n-1个元素移入m_pOut

            return m_pIn->front();//再把m_pIn最后的那个元素弹栈

            //swap();//然后在交换进队列和出队列的角色
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current quene");
        }
    }
    void clear()        //O(n)
    {
        m_quene_in.clear();
        m_quene_out.clear();
    }
    int size()const //O(1)
    {
        return (m_quene_in.length() + m_quene_out.length());
    }

};


int main()
{

     QueneToStack<int> qs;

    for(int i=0; i<10; i++)
    {
        qs.push(i);
    }

    while(qs.size() > 0)
    {
        cout << qs.top() << endl;

        qs.pop();
    }


    return 0;
}
