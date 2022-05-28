#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"

namespace DTLib {




template <typename V, typename E>
class ListGraph : public Graph<V,E>
{
protected:
    struct Edge : public Object
    {
        int b;  //起点
        int e;  //终点
        E data; //权值
    };

    struct Vertex : public Object
    {
        V* data;
        LinkList<Edge> edge;
    };
public:
    ListGraph() {}

    /*新增加的公有成员函数*/
    int addVertex();
    int addVertex(const V& value);
    void removeVertex();
};

}

#endif // LISTGRAPH_H
