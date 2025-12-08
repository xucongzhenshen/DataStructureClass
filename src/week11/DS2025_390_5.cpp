#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>

// 有向无环图类
class DirectedGraph
{
private:
    int V;                             // 顶点数
    std::vector<std::vector<int>> adj; // 邻接表
    std::vector<int> inDegree;         // 入度数组

public:
    // 构造函数
    DirectedGraph(int vertices) : V(vertices), adj(vertices), inDegree(vertices, 0) {}

    // 添加有向边
    void addEdge(int from, int to)
    {
        if (from < 0 || from >= V || to < 0 || to >= V)
        {
            throw std::out_of_range("顶点索引超出范围");
        }
        adj[from].push_back(to);
        inDegree[to]++;
    }

    // 获取顶点数
    int getVertexCount() const { return V; }

    // 获取邻接表
    const std::vector<std::vector<int>> &getAdjacencyList() const { return adj; }

    // 获取入度数组
    const std::vector<int> &getInDegree() const { return inDegree; }

    // 拓扑排序（返回排序结果）
    std::vector<int> topologicalSort() const
    {
        std::vector<int> result;
        std::vector<int> tempInDegree = inDegree;
        std::queue<int> zeroInDegreeQueue;

        // 找到所有入度为0的顶点
        for (int i = 0; i < V; i++)
        {
            if (tempInDegree[i] == 0)
            {
                zeroInDegreeQueue.push(i);
            }
        }

        // 处理队列中的顶点
        while (!zeroInDegreeQueue.empty())
        {
            int vertex = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
            result.push_back(vertex);

            // 减少相邻顶点的入度
            for (int neighbor : adj[vertex])
            {
                tempInDegree[neighbor]--;
                if (tempInDegree[neighbor] == 0)
                {
                    zeroInDegreeQueue.push(neighbor);
                }
            }
        }

        // 检查是否有环
        if (result.size() != V)
        {
            throw std::runtime_error("图中存在环，无法进行拓扑排序");
        }

        return result;
    }
};

// 拓扑排序迭代器类
class TopoIterator
{
private:
    const DirectedGraph *graph;
    std::vector<int> topologicalOrder;
    size_t currentIndex;

public:
    // 构造函数
    TopoIterator(const DirectedGraph &g) : graph(&g), currentIndex(0)
    {
        topologicalOrder = g.topologicalSort();
    }

    // 复制构造函数
    TopoIterator(const TopoIterator &other)
        : graph(other.graph),
          topologicalOrder(other.topologicalOrder),
          currentIndex(other.currentIndex) {}

    // 获取起始迭代器
    static TopoIterator begin(const DirectedGraph &g)
    {
        return TopoIterator(g);
    }

    // 获取结束迭代器
    static TopoIterator end(const DirectedGraph &g)
    {
        TopoIterator iter(g);
        iter.currentIndex = iter.topologicalOrder.size();
        return iter;
    }

    // 前向遍历操作
    // 解引用操作符
    int operator*() const
    {
        if (currentIndex >= topologicalOrder.size())
        {
            throw std::out_of_range("迭代器已到达末尾");
        }
        return topologicalOrder[currentIndex];
    }

    // 前置递增操作符
    TopoIterator &operator++()
    {
        if (currentIndex < topologicalOrder.size())
        {
            currentIndex++;
        }
        return *this;
    }

    // 后置递增操作符
    TopoIterator operator++(int)
    {
        TopoIterator temp = *this;
        ++(*this);
        return temp;
    }

    // 相等比较操作符
    bool operator==(const TopoIterator &other) const
    {
        return graph == other.graph && currentIndex == other.currentIndex;
    }

    // 不等比较操作符
    bool operator!=(const TopoIterator &other) const
    {
        return !(*this == other);
    }

    // 检查是否到达末尾
    bool isEnd() const
    {
        return currentIndex >= topologicalOrder.size();
    }

    // 重置迭代器
    void reset()
    {
        currentIndex = 0;
    }

    // 获取当前位置
    size_t getCurrentPosition() const
    {
        return currentIndex;
    }

    // 获取拓扑顺序
    const std::vector<int> &getTopologicalOrder() const
    {
        return topologicalOrder;
    }
};

// 使用示例
int main()
{
    // 创建有向无环图
    DirectedGraph graph(6);

    // 添加边
    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    std::cout << "使用迭代器遍历拓扑顺序:" << std::endl;

    // 创建迭代器并遍历
    TopoIterator iter = TopoIterator::begin(graph);
    TopoIterator endIter = TopoIterator::end(graph);

    // 使用迭代器遍历
    for (; iter != endIter; ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}