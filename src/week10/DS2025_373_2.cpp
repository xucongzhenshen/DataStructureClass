#include <iostream>
#include <vector>
#include <climits> // 用于INT_MAX
using namespace std;

// 函数：计算从顶点0到DAG中所有其他顶点的最短路径长度
// 参数：
//   n: 顶点数量
//   graph: 图的邻接表表示，graph[i]是一个vector<pair<int, int>>，其中每个pair表示边 (i, j) 和权重
// 返回值：一个向量dist，其中dist[i]表示从顶点0到顶点i的最短路径长度。如果不可达，则值为INT_MAX
vector<int> shortestPathInDAG(int n, const vector<vector<pair<int, int>>> &graph)
{
    // 初始化距离数组，所有顶点初始不可达，除了顶点0
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    // 按照顶点编号顺序遍历所有顶点（从0到n-1）
    for (int i = 0; i < n; i++)
    {
        // 如果顶点i不可达，则跳过（因为无法从0到达i）
        if (dist[i] == INT_MAX)
        {
            continue;
        }

        // 遍历顶点i的所有出边
        for (const auto &edge : graph[i])
        {
            int j = edge.first;       // 目标顶点j
            int weight = edge.second; // 边权

            // 更新顶点j的距离：如果通过i到j的路径更短，则更新
            if (dist[i] + weight < dist[j])
            {
                dist[j] = dist[i] + weight;
            }
        }
    }

    return dist;
}

// 测试代码
int main()
{
    // 示例：构建一个DAG，有4个顶点（0到3）
    // 边：0->1 (权重2), 0->2 (权重3), 1->3 (权重1)
    int n = 4;
    vector<vector<pair<int, int>>> graph(n);

    graph[0].push_back({1, 2});
    graph[0].push_back({2, 3});
    graph[1].push_back({3, 1});

    vector<int> distances = shortestPathInDAG(n, graph);

    // 输出距离
    for (int i = 0; i < n; i++)
    {
        if (distances[i] == INT_MAX)
        {
            cout << "Distance to node " << i << ": unreachable" << endl;
        }
        else
        {
            cout << "Distance to node " << i << ": " << distances[i] << endl;
        }
    }

    return 0;
}

// time complexity: O(V + E), where V is the number of vertices 
// and E is the number of edges in the DAG.
// Prove: The algorithm processes each vertex once in the outer loop, 
// and each edge once in the inner loop, 
// resulting in a total time complexity proportional to the sum of vertices and edges.