#pragma once
#include <vector>
#include <iostream>

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

class Set{
private:
    std::vector<int> parent;
    int count;
public:
    Set(int n) : parent(n), count(n)
    {
        std::fill(parent.begin(), parent.end(), -1);
    }
    bool unionSets(int i, int j)
    {
        int rootI = collapsingFind(i);
        int rootJ = collapsingFind(j);
        if (rootI == rootJ)
            return false;
        if(parent[rootI] < parent[rootJ]) // rootI has larger size
        {
            parent[rootI] += parent[rootJ];
            parent[rootJ] = rootI;
        }
        else
        {
            parent[rootJ] += parent[rootI];
            parent[rootI] = rootJ;
        }
        count--;
        return true;
    }
    int collapsingFind(int i)
    {
        int root = i; for (; parent[root] >= 0; root = parent[root]);
        while(i != root)
        {
            int temp = parent[i];
            parent[i] = root;
            i = temp;
        }
        return root;
    }
};