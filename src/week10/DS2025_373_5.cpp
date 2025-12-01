#include <iostream>
#include <vector>
#include <climits> // 用于INT_MAX
using namespace std;

// 函数：使用Prim算法计算最小成本生成树的总成本
// 参数：
//   graph: 图的邻接矩阵表示，graph[i][j]表示边(i, j)的权重。图是无向的，因此矩阵应对称。
//          如果边不存在，则权重应为INT_MAX。
//   n: 顶点的数量
// 返回值：最小生成树的总成本。如果图不连通，返回INT_MAX（表示无生成树）。
int primMST(const vector<vector<int>> &graph, int n)
{
    // 初始化key数组和mstSet数组
    vector<int> key(n, INT_MAX);
    vector<bool> mstSet(n, false);

    // 从顶点0开始生成MST
    key[0] = 0;
    int totalCost = 0;

    // 循环n-1次，每次添加一个顶点到MST
    for (int count = 0; count < n - 1; count++)
    {
        // 选择key值最小且不在mstSet中的顶点u
        int u = -1;
        int minKey = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (!mstSet[i] && key[i] < minKey)
            {
                minKey = key[i];
                u = i;
            }
        }

        // 如果找不到合适的顶点，说明图不连通，返回INT_MAX
        if (u == -1)
        {
            return INT_MAX;
        }

        // 将顶点u加入MST
        mstSet[u] = true;
        totalCost += key[u]; // 累加生成树的成本

        // 更新u的所有邻居顶点的key值
        for (int v = 0; v < n; v++)
        {
            // 如果边(u, v)存在（权重不为INT_MAX），且v不在MST中，且边权重小于当前key[v]
            if (graph[u][v] != INT_MAX && !mstSet[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
            }
        }
    }

    return totalCost;
}

// 测试代码
int main()
{
    // 示例：构建一个无向图的邻接矩阵，有4个顶点
    int n = 4;
    vector<vector<int>> graph = {
        {0, 2, 3, INT_MAX},
        {2, 0, 1, 4},
        {3, 1, 0, 5},
        {INT_MAX, 4, 5, 0}};

    int cost = primMST(graph, n);
    if (cost == INT_MAX)
    {
        cout << "The graph is not connected. No spanning tree exists." << endl;
    }
    else
    {
        cout << "Total cost of minimum spanning tree: " << cost << endl;
    }

    return 0;
}

// time complexity: O(V^2), where V is the number of vertices in the graph.
// Prove: The algorithm contains a loop that runs V times to add vertices to the MST,
// and within that loop, it searches for the minimum key value among V vertices,
// resulting in a total time complexity of O(V^2).