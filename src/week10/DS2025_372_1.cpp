#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 函数：计算从根节点到树中所有其他顶点的最短路径长度
// 参数：
//   root: 根节点的索引（整数）
//   graph: 树的邻接表表示，graph[u]是一个pair列表，每个pair为(邻居节点, 边长度)
// 返回值：一个向量dist，其中dist[i]表示从根节点到节点i的路径长度
vector<int> shortestPathInTree(int root, const vector<vector<pair<int, int>>> &graph)
{
    int n = graph.size();    // 顶点数量
    vector<int> dist(n, -1); // 初始化距离数组，-1表示未访问
    queue<int> q;            // BFS队列

    // 从根节点开始
    dist[root] = 0;
    q.push(root);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        // 遍历u的所有邻居
        for (const auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            // 如果邻居v未被访问，更新其距离并加入队列
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + weight;
                q.push(v);
            }
        }
    }

    return dist;
}

// 测试代码
int main()
{
    // 示例：构建一个树，有4个节点，根节点为0
    // 节点0连接节点1（边长为2）和节点2（边长为3）
    // 节点1连接节点3（边长为1）
    int n = 4;
    vector<vector<pair<int, int>>> graph(n);

    graph[0].push_back({1, 2});
    graph[0].push_back({2, 3});
    graph[1].push_back({0, 2});
    graph[1].push_back({3, 1});
    graph[2].push_back({0, 3});
    graph[3].push_back({1, 1});

    int root = 0;
    vector<int> distances = shortestPathInTree(root, graph);

    // 输出距离
    for (int i = 0; i < n; i++)
    {
        cout << "Distance to node " << i << ": " << distances[i] << endl;
    }

    return 0;
}
// time complexity: O(V), where V is the number of vertices.
// Prove: The algorithm performs a BFS traversal, 
// visiting each vertex once, 
// resulting in a total time complexity proportional to the number of vertices.