#include "union.h"
#include <iostream>

int main()
{
    int n = 10;
    UnionFind uf(n);

    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(4, 5);
    uf.unite(5, 6);
    uf.unite(7, 5);
    uf.unite(8, 9);

    for (int i = 0; i < n/2; ++i)
    {
        int root = uf.find_with_splitting(i);
        std::cout << "Element: " << i << ", Root: " << root << std::endl;
    }
    for(int i = n/2; i < n; ++i)
    {
        int root = uf.find_with_halving(i);
        std::cout << "Element: " << i << ", Root: " << root << std::endl;
    }

    std::cout << "Number of connected components: " << uf.getCount() << std::endl;

    return 0;
}