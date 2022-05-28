#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DTLib {

template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;

public:
    MatrixGraph()
    {
        /*初始化点和边的值*/
        for(int i=0; i<vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(int j=0; j<vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }

        m_eCount = 0;
    }

    /*获取顶点i所关联的数据元素的值*/
    V getVertex(int i)
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    /*获取顶点i所关联的数据元素的值*/
    bool getVertex(int i, V& value)
    {
        bool ret = ( (0<=i) && (i<vCount() ) );

        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    /*设置顶点i相关联的数据元素的值*/
    bool setVertex(int i, const V& value)
    {
        bool ret = ( (0<=i) && (i<vCount() ) );

        if(ret)
        {
            /*使用一个中间变量data，防止*(m_vertexes[i]) = value如此赋值的异常安全*/
            V* data = m_vertexes[i];

            if(data == NULL)
            {
                data = new V();
            }

            if(data != NULL)
            {
                /*
                 * 原因：这个赋值有可能是异常返回，不是异常安全的，但是如果赋值失败，则这个图对象就无法使用
                 * *(m_vertexes[i]) = value;
                */

                *(data) = value;

                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
            }

        }

        return ret;
    }

    /*获取顶点i相邻接的其他顶点*/
    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL; //定义一个动态数组

        if( (0<=i) && (i<vCount()) )//判断参数是否合法
        {
            int n = 0;//定义一个标记变量

            //记录第i行有几个非0数值
            for(int j=0; j<vCount(); j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);//给动态数组赋值

            if(ret != NULL)//判断动态数组是否为空
            {
                for(int j=0,k=0; j<vCount(); j++)
                {
                    if(m_edges[i][j] != NULL)
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object...");//为空就报异常
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");//不合法就报异常
        }

        return ret;
    }

    /*获取顶点i和顶点j之间的权值*/
    E getEdge(int i, int j)
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }

    /*获取顶点i和顶点j之间的权值的另一个函数，适配上面的函数*/
    bool getEdge(int i, int j, E& value)
    {
        bool ret = ( (0<=i) && ( i<vCount() ) &&
                    (0<=j) && ( j<vCount() )  );

        if(ret)//判断i,j是否合法
        {
            if(m_edges[i][j] != NULL)//判断第i个顶点和第j个顶点是否有权值
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    /*设置(i,j)的某条边*/
    bool setEdge(int i, int j, const E& value)
    {
        bool ret = ( (0<=i) && ( i<vCount() ) &&
                    (0<=j) && ( j<vCount() )  );

        if(ret)//判断i,j是否合法
        {
            E* ne = m_edges[i][j];//同样为了异常安全，采取一个中间变量

            //判断ne是否为空
            if(ne == NULL)
            {
                ne = new E();//如果是空，则申请一个空间

                if(ne != NULL)
                {
                    *ne = value;//赋值

                    m_edges[i][j] = ne;//再将这个值赋给边

                    m_eCount++; //总变数要加1
                }
                else//申请失败就抛异常
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new edge value...");
                }
            }
            else
            {
                *ne = value;//不为空直接赋值即可
            }
        }

        return ret;
    }

    /*移除(i,j)的某条边*/
    bool removeEdge(int i, int j)
    {
        bool ret = ( (0<=i) && ( i<vCount() ) &&
                    (0<=j) && ( j<vCount() )  );

        if(ret)//判断i,j是否合法
        {
            E* toDel = m_edges[i][j];//利用中间变量获取边的值，为了尽量达到异常安全的目的，采用中间变量接管

            m_edges[i][j] = NULL;//将边的值赋值为空

            if(toDel != NULL)//判断待删除的是否为空
            {
                m_eCount--;//变数减一

                delete toDel;
            }
        }

        return ret;
    }

    /*获取顶点的数目*/
    int vCount()
    {
        return N;
    }

    /*获取边的数目*/
    int eCount()
    {
        return m_eCount;
    }

    /*获取顶点i的出度，数一数对应行有几个不为0的值*/
    int OD(int i)
    {
        int ret = 0;

        if( (0<=i) && (i<vCount()) )
        {
            for(int j=0; j<vCount(); j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");//不合法就报异常
        }

        return ret;
    }

    /*获取顶点i的入度，数一数对应列有几个不为0的值*/
    int ID(int i)
    {
        int ret = 0;

        if( (0<=i) && (i<vCount()) )
        {
            for(int j=0; j<vCount(); j++)
            {
                if(m_edges[j][i] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");//不合法就报异常
        }

        return ret;
    }


    ~MatrixGraph()
    {
        for(int i=0; i<vCount(); i++)
        {
            for(int j=0; j<vCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }
};

}

#endif // MATRIXGRAPH_H
