#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib {

template<typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity; //顺序存储空间的大小
public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if(this->m_array != NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    /*重新设置顺序存储空间的大小*/
    void resize(int capacity)
    {
        if(capacity != m_capacity)
        {
            T* array = new T[capacity];

            if(array != NULL)
            {
                //先比较两个数组的长度
                int length = (this->m_length < capacity ? this->m_length : capacity);

                //再复制,数据元素不能丢失
                for(int i=0; i<length; i++)
                {
                    array[i] = this->m_array[i];//如果在这里发生异常，那也不会怎么样，三个值并没有改变
                }

                //保存重置前的顺序存储空间的地址
                T* temp = this->m_array;//delete会触发析构函数的调用，
                                        //由于某些原因会抛出异常(如果在这里发生异常)，那么函数执行到这里就会异常返回。所以先用一个temp保存地址，之后赶紧赋值，再delete

                //重新赋值
                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;

                //释放之前的存储空间
                delete[] temp;//即使在这里抛出异常，那么前三个值已经被保存了
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
            }
        }
    }
    ~DynamicList()//归还空间
    {
        delete[] this->m_array;
    }
};
}


#endif // DYNAMICLIST_H
