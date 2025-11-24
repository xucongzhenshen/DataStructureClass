#include "AdjacencyMultilist.h"
#include <sstream>
#include <iostream>

int main()
{
    AdjMulGraph<int> graph;
    // sample weighted undirected graph from week9 markdown
    std::istringstream input("W\n0 1 4\n0 2 3\n1 2 1\n1 3 2\n2 3 4\n3 4 2\n4 0 7\n5 6 1\n6 5 1\n8 9 5\n9 8 5\n9 10 2\n10 8 3\n2 10 6\n4 5 8\n");
    
    graph.readFromStream(input);
    std::cout << "Graph edges:\n";
    graph.printAdjMulList();

    auto mst = graph.kruskalMST();
    std::cout << "\nKruskal's MST edges:\n";
    for (const auto& edge : mst)
    {
        std::cout << edge->vertex1 << " - " << edge->vertex2 << " (weight: " << edge->weight << ")\n";
    }
    return 0;
}