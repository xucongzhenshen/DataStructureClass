#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 检查当前颜色分配是否有效
bool isValidColor(const vector<vector<int>> &G, const vector<int> &colors, int node, int color)
{
    for (int i = 0; i < G.size(); i++)
    {
        if (G[node][i] == 1 && colors[i] == color)
        {
            return false;
        }
    }
    return true;
}

// 使用栈实现的图着色函数
vector<int> graphColoring(const vector<vector<int>> &G)
{
    int n = G.size();
    vector<int> colors(n, 0); // 存储每个节点的颜色，0表示未着色

    // 使用栈来存储状态：节点索引和尝试的颜色
    stack<pair<int, int>> stateStack;

    // 从第一个节点开始
    int currentNode = 0;
    int tryColor = 1;

    while (currentNode < n)
    {
        bool colorAssigned = false;

        // 尝试为当前节点分配颜色
        while (tryColor <= 4)
        {
            if (isValidColor(G, colors, currentNode, tryColor))
            {
                // 找到有效颜色
                colors[currentNode] = tryColor;
                stateStack.push({currentNode, tryColor});
                currentNode++;
                tryColor = 1;
                colorAssigned = true;
                break;
            }
            tryColor++;
        }

        // 如果无法为当前节点分配颜色，需要回溯
        if (!colorAssigned)
        {
            if (stateStack.empty())
            {
                return vector<int>();
            }

            // 回溯到上一个节点
            auto prevState = stateStack.top();
            stateStack.pop();
            currentNode = prevState.first;
            tryColor = prevState.second + 1;
            colors[currentNode] = 0; // 重置当前节点颜色
        }
    }

    return colors;
}

// 打印着色结果
void printColoring(const vector<int> &colors)
{
    if (colors.empty())
    {
        cout << "No valid coloring found." << endl;
        return;
    }
    for (int i = 0; i < colors.size(); i++)
    {
        cout << "Node " << i << ": Color " << colors[i] << endl;
    }
}

// 测试函数
int main()
{
    vector<vector<int>> G2 = {
        {0, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}};

    vector<int> result2 = graphColoring(G2);
    printColoring(result2);
    return 0;
}
