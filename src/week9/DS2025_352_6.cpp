#include <iostream>
#include <sstream>
#include "Graph.h"

int main()
{
    // sample graph: 4 vertices, 4 edges
    // edges: 0-1, 0-2, 1-2, 2-3
    std::istringstream ss("4 4\n0 1\n0 2\n1 2\n2 3\n");
    Graph g;
    g.readFromStream(ss);

    std::cout << "Adjacency list:\n";
    g.printAdjList();

    auto order0 = g.dfs(0);
    std::cout << "DFS from 0: ";
    for (int v : order0)
        std::cout << v << " ";
    std::cout << "\n";

    auto order1 = g.dfs(1);
    std::cout << "DFS from 1: ";
    for (int v : order1)
        std::cout << v << " ";
    std::cout << "\n";

    auto bfs0 = g.bfs(0);
    std::cout << "BFS from 0: ";
    for (int v : bfs0)
        std::cout << v << " ";
    std::cout << "\n";

    return 0;
}
