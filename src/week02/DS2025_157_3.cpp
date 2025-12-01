#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
using namespace std;

// 方向定义：东、东南、南、西南、西、西北、北、东北
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

bool recursivePath(vector<vector<int>> &maze, vector<vector<bool>> &mark,
                   int i, int j, int m, int p, vector<pair<int, int>> &path)
{
    // 边界和可达性检查
    if (i < 0 || i >= m || j < 0 || j >= p)
        return false;
    if (maze[i][j]) // 非 0 表示障碍
        return false;
    if (mark[i][j]) // 已访问
        return false;

    // 标记当前单元格已访问并加入路径
    mark[i][j] = true;
    path.push_back({i, j});

    // 到达终点
    if (i == m - 1 && j == p - 1)
    {
        return true;
    }

    // 尝试所有8个方向
    for (int dir = 0; dir < 8; dir++)
    {
        int g = i + dx[dir];
        int h = j + dy[dir];

        if (recursivePath(maze, mark, g, h, m, p, path))
        {
            return true;
        }
    }

    // 回溯：移除当前单元格
    path.pop_back();
    return false;
}

// 包装函数
bool findPathRecursive(vector<vector<int>> &maze, int start_i, int start_j,
                       vector<pair<int, int>> &path)
{
    int m = maze.size();
    int p = maze[0].size();
    // 基本合法性检查
    if (m == 0 || p == 0)
        return false;
    if (start_i < 0 || start_i >= m || start_j < 0 || start_j >= p)
        return false;
    if (maze[start_i][start_j]) // 起点被障碍挡住
        return false;

    vector<vector<bool>> mark(m, vector<bool>(p, false));
    return recursivePath(maze, mark, start_i, start_j, m, p, path);
}

// 测试函数
void testMazeSolver()
{
    // 测试迷宫 5x5
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}};

    vector<pair<int, int>> path;

    if (findPathRecursive(maze, 0, 0, path))
    {
        cout << "Path found!" << endl;
        int steps = path.empty() ? 0 : static_cast<int>(path.size()) - 1;
        cout << "Path length (steps): " << steps << endl;
        cout << "Path: ";
        for (auto &p : path)
        {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found!" << endl;
    }
}

// 性能测试：最坏情况下的时间复杂度
void performanceTest()
{
    int m = 6, p = 6;
    vector<vector<int>> emptyMaze(m, vector<int>(p, 0)); // 无障碍迷宫

    vector<pair<int, int>> path;

    auto start = chrono::high_resolution_clock::now();
    bool found = findPathRecursive(emptyMaze, 0, 0, path);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time for " << m << "x" << p << " maze: " << duration.count() << " microseconds" << endl;
    if (found)
    {
        int steps = path.empty() ? 0 : static_cast<int>(path.size()) - 1;
        cout << "Path length (steps): " << steps << endl;
    }
    else
    {
        cout << "No path found in performance test." << endl;
    }
}

int main()
{
    cout << "=== Maze Solver Test ===" << endl;
    testMazeSolver();

    cout << "\n=== Performance Test ===" << endl;
    performanceTest();

    return 0;
}

/*
Complexity Analysis:
In the worst-case scenario, the recursive backtracking algorithm explores
all possible paths in the maze. For an m x p maze, there are up to 8 possible
directions to move from each cell in the longest path. Therefore, the time
complexity can be approximated as O(m*p) in the absolute worst case, where every cell is
empty and the algorithm explores every possible path.
*/