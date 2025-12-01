#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "union.h"

template <typename T>
struct EdgeNode
{
    int mark; // 标记位，用于标记边是否被访问过
    int vertex1;
    int vertex2;
    EdgeNode *path1; // 指向vertex1的下一条边
    EdgeNode *path2; // 指向vertex2的下一条边
    // 可以添加其他边信息，如权重等
    T weight;
};

template <typename T>
class AdjMulGraph
{
    int n;                              // 顶点数
    int m;                              // 边数
    std::vector<EdgeNode<T> *> vertexHead; // 每个顶点指向第一条边
    std::vector<EdgeNode<T> *> edgeList;   // 所有边的列表
public:
    AdjMulGraph() : n(0), m(0) {}
    ~AdjMulGraph()
    {
        for (auto e : edgeList)
            delete e;
    }
    void readFromStream(std::istream &is)
    {
        n = 0;
        m = 0;
        vertexHead.clear();
        edgeList.clear();
        std::string is_weighted;
        is >> is_weighted;
        if(is_weighted != "W" && is_weighted != "UW")
        {
            std::cerr << "First input should be 'W' (weighted) or 'UW' (unweighted)\n";
            return;
        }
        bool weighted = (is_weighted == "W");
        if(weighted)
        {
            int u, v;
            T w;
            while (is >> u >> v >> w)
            {
                int maxVertex = std::max(u, v);
                if (maxVertex >= n)
                {
                    vertexHead.resize(maxVertex + 1, nullptr);
                    n = maxVertex + 1;
                }
                EdgeNode<T> *e = new EdgeNode<T>{0, u, v, vertexHead[u], vertexHead[v], w};
                vertexHead[u] = e;
                vertexHead[v] = e;
                edgeList.push_back(e);
                ++m;
            }
            return;
        }
        int u, v;
        while (is >> u >> v)
        {
            int maxVertex = std::max(u, v);
            if (maxVertex >= n)
            {
                vertexHead.resize(maxVertex + 1, nullptr);
                n = maxVertex + 1;
            }
            EdgeNode<T> *e = new EdgeNode<T>{0, u, v, vertexHead[u], vertexHead[v], T()};
            vertexHead[u] = e;
            vertexHead[v] = e;
            edgeList.push_back(e);
            ++m;
        }
    }
    std::vector<int> dfs(int start) const
    {
        std::vector<int> order;
        if (start < 0 || start >= n)
            return order;
        std::vector<char> vis(n, 0);
        std::vector<int> stack;
        stack.push_back(start);
        while (!stack.empty())
        {
            int u = stack.back();
            stack.pop_back();
            if (vis[u])
                continue;
            vis[u] = 1;
            order.push_back(u);
            // 遍历邻接多重表中的边
            for (EdgeNode<T> *e = vertexHead[u]; e != nullptr; )
            {
                int v = (e->vertex1 == u) ? e->vertex2 : e->vertex1;
                if (!vis[v])
                    stack.push_back(v);
                e = (e->vertex1 == u) ? e->path1 : e->path2;
            }
        }
        return order;
    }
    void printAdjMulList() const
    {
        for (int i = 0; i < n; ++i)
        {
            std::cout << "Vertex " << i << ": ";
            for (EdgeNode<T> *e = vertexHead[i]; e != nullptr; )
            {
                int v = (e->vertex1 == i) ? e->vertex2 : e->vertex1;
                std::cout << "-> " << v << " ";
                e = (e->vertex1 == i) ? e->path1 : e->path2;
            }
            std::cout << "-> NULL\n";
        }
    }
    std::vector<EdgeNode<T> *> kruskalMST() const
    {
        Set uf(n);
        std::vector<EdgeNode<T> *> mst;
        std::vector<EdgeNode<T> *> sortedEdges = edgeList;
        std::sort(sortedEdges.begin(), sortedEdges.end(), [](EdgeNode<T> *a, EdgeNode<T> *b) {
            return a->weight < b->weight;
        });
        for (auto e : sortedEdges)
        {
            if (uf.unionSets(e->vertex1, e->vertex2))
            {
                mst.push_back(e);
                if (mst.size() == n - 1)
                    break;
            }
        }
        return mst;
    }
};