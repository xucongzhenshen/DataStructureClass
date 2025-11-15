#pragma once
#include <vector>

class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int count;
public:
    UnionFind(int n) : parent(n), rank(n, 0), count(n)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }
    int find(int p)
    {
        if (parent[p] != p)
        {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }
    void unite(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP != rootQ)
        {
            if (rank[rootP] < rank[rootQ])
            {
                parent[rootP] = rootQ;
            }
            else if (rank[rootP] > rank[rootQ])
            {
                parent[rootQ] = rootP;
            }
            else
            {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }
            count--;
        }
    }
    int getCount() const
    {
        return count;
    }

    int find_with_splitting(int p)
    {
        while(parent[p] != p)
        {
            int temp = parent[p];
            parent[p] = parent[parent[p]];
            p = temp;
        }
        return p;
    }
    int find_with_halving(int p)
    {
        while(parent[p] != p)
        {
            p = parent[p] = parent[parent[p]];
        }
        return p;
    }
};