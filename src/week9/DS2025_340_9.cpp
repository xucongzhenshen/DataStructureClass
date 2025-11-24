#include <iostream>
#include <sstream>
#include <vector>
#include "Graph.h"
int main()
{
    Graph g;
    // sample input 4 vertices, 4 edges
    std::istringstream input("4 4\n0 1\n0 3\n1 2\n3 2\n");
    g.readFromStream(input);
    std::cout << "Adjacency List (sample):\n";
    g.printAdjList();
    return 0;
}

// Time Complexity: 
// O(n + m) where n is number of vertices and m is number of edges