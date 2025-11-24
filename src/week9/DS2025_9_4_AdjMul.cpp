#include "AdjacencyMultilist.h"
#include <sstream>
#include <iostream>

int main()
{
    AdjMulGraph<int> g;
    // sample undirected graph from week9 markdown
    // 5 vertices, edges: 0-1, 0-3, 1-2, 3-2, 4-0, 4-1, 4-2
    std::istringstream input("UW\n0 1\n0 3\n1 2\n3 2\n4 0\n4 1\n4 2\n");
    g.readFromStream(input);
    std::cout << "Adjacency Multilist:\n";
    g.printAdjMulList();

    auto order = g.dfs(0);
    std::cout << "DFS order starting from 0: ";
    for (int v : order)
        std::cout << v << " ";
    std::cout << std::endl;

    // Also test DFS from another start
    auto order2 = g.dfs(1);
    std::cout << "DFS order starting from 1: ";
    for (int v : order2)
        std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}