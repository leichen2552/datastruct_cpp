#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace DTLib {

class Sort:public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator =(const Sort&);

    template <typename T>
    static void Swap(T& a,T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid ,int end, bool min2max)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while( (i <= mid) && (j <= end))
        {
            if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
            {
                helper[k++] = src[i++];
            }
            else
            {
                helper[k++] = src[j++];
            }
        }


        while(i <= mid)
        {
            helper[k++] = src[i++];
        }
        while(j <= end)
        {
            helper[k++] = src[j++];
        }

        for(i=begin; i<=end; i++)//这里 少些一个等于号，找了一个小时
        {
            src[i] = helper[i];
        }
    }

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool min2max)//希尔排序是一种不稳定的排序法
    {
        if(begin < end)
        {
            int mid = (begin + end) / 2;

            Merge(src, helper, begin, mid, min2max);
            Merge(src, helper, mid+1, end, min2max);
            Merge(src, helper, begin, mid, end, min2max);
        }
    }


    template <typename T>
    static int Partition(T array[], int begin, int end, bool min2max)//快速排序的划分函数
    {
        T pv = array[begin];

        while(begin < end)
        {
            while((begin < end) && (min2max ? (array[end] > pv) :(array[end] < pv)))
            {
                end--;
            }
            Swap(array[begin], array[end]);

            while((begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv)))
            {
                begin++;
            }

            Swap(array[begin],array[end]);
        }

        array[begin] = pv;

        return begin;
    }

    template <typename T>
    static void Quick(T array[], int begin, int end, bool min2Max)//快速排序真正的递归函数
    {
        if(begin < end)
        {
            int pivot = Partition(array, begin, end,min2Max);

            Quick(array, begin, pivot-1, min2Max);
            Quick(array, pivot+1, end, min2Max);
        }
    }

public:
    template <typename T>
    static void Select(T array[], int len, bool min2Max = true)//选择排序是不稳定的排序法O(n2)
    {
        for(int i=0; i<len; i++)//第i次 从后面 第n-i个元素 选出关键字最小的元素
        {
            int min = i;

            for(int j=i+1; j<len; j++)
            {
                if(min2Max ? (array[min] > array[j]) : (array[min] < array[j]))//这里是选择最小值，是从小到大排序
                {
                    min = j;
                }
            }

            if(min != i)//排除两个相等的元素交换
            {
                Swap(array[i],array[min]);
            }

        }
    }

    template <typename T>
    static void Insert(T array[], int len, bool min2Max = true)//插入排序是稳定的排序法O(n2)
    {
        for(int i=1; i<len; i++)//从第1个元素开始，是因为第0个元素不用插入就是第一个位置，这也是一种优化
        {
            int k = i;

            T e = array[i];

/*这一段代码进行优化
            for(int j=i-1; j>=0; j--)//是从后向前比较的,比较一次移动一次
            {
                if(array[j] > e)
                {
                    array[j+1] = array[j];//把前一个元素向后挪动一个位置
                    k = j;//记录可能的位置
                }
                else
                {
                    break;
                }
            }
*/
            for(int j=i-1; (j>=0)&&(min2Max ? (array[j] > e):(array[j] < e)); j--)
            {
                array[j+1] = array[j];
                k = j;
            }

            if(k != i)
            {
                array[k] = e;
            }
        }
    }

    template <typename T>
    static void Bubble(T array[], int len, bool min2Max = true)//冒泡排序是稳定的排序法O(n2)
    {
        bool exchange = true;//如果没有发生交换，就说明已经排序完成

        for(int i=0; (i<len) && exchange; i++)
        {
            for(int j = len-1;j>i;j--)
            {
                if((min2Max)?(array[j] < array[j-1]):(array[j] > array[j-1]))
                {
                    Swap(array[j], array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    //在计算机发展的早期，认为排序的时间复杂度都是O(n2)，后来划时代的希尔排序出来了
    template <typename T>
    static void Shell(T array[], int len, bool min2Max = true)//希尔排序是一种不稳定的排序法O(n3/2)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;//实践证明这样子是比较好的

//分组之后使用插入排序
            for(int i=d; i<len; i+=d)
            {
                int k = i;
                T e = array[i];

                for(int j=i-d; (j>=0)&&(min2Max ? (array[j] > e):(array[j] < e)); j-=d)
                {
                    array[j+d] = array[j];
                    k = j;
                }

                if(k != i)
                {
                    array[k] = e;
                }
            }
//分组之后可以采用冒泡排序试试看：

        }while(d > 1);
    }

    template <typename T>
    static void Merge(T array[], int len, bool min2Max = true)//归并排序是一种稳定的排序法O(n*logn)
    {
        T* helper = new T[len];

        if(helper != NULL)
        {
            Merge(array, helper, 0, len-1, min2Max);
        }

        delete[] helper;
    }

    template <typename T>
    static void Quick(T array[], int len, bool min2Max = true)//快速排序是一种不稳定的排序法O(n*logn)
    {
        Quick(array, 0, len-1, min2Max);
    }

//排序类和数组类之间的关系
    template <typename T>
    static void Select(Array<T>& array, bool min2Max = true)
    {
        Select(array.array(), array.length(), min2Max);
    }

    template <typename T>
    static void Insert(Array<T>& array, bool min2Max = true)
    {
        Insert(array.array(), array.length(), min2Max);
    }

    template <typename T>
    static void Bubble(Array<T>& array, bool min2Max = true)
    {
        Bubble(array.array(), array.length(), min2Max);
    }

    template <typename T>
    static void Shell(Array<T>& array, bool min2Max = true)
    {
        Shell(array.array(), array.length(), min2Max);
    }

    template <typename T>
    static void Merge(Array<T>& array, bool min2Max = true)
    {
        Merge(array.array(), array.length(), min2Max);
    }

    template <typename T>
    static void Quick(Array<T>& array, bool min2Max = true)
    {
        Quick(array.array(), array.length(), min2Max);
    }

};

}


#endif // SORT_H
