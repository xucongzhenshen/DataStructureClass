#include "Graph.h"
#include <sstream>
#include <iostream>

int main()
{
    Graph g;
    // sample undirected graph from week9 markdown
    // 4 vertices, edges: 0-1, 0-3, 1-2, 3-2
    std::istringstream input("5 7\n0 1\n0 3\n1 2\n3 2\n4 0\n4 1\n4 2\n");
    g.readFromStream(input);
    std::cout << "Adjacency List:\n";
    g.printAdjList();

    auto order = g.bfs(0);
    std::cout << "BFS order starting from 0: ";
    for (int v : order)
        std::cout << v << " ";
    std::cout << std::endl;

    // Also test BFS from another start
    auto order2 = g.bfs(1);
    std::cout << "BFS order starting from 1: ";
    for (int v : order2)
        std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}