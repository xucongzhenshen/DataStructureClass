#pragma once
#include <iostream>
#include <vector>

struct AdjNode
{
    int v;
    AdjNode *next;
    AdjNode(int vv) : v(vv), next(nullptr) {}
};

class Graph
{
    int n;
    int m;
    std::vector<AdjNode *> head;
    std::vector<AdjNode *> tail; // keep tails to append and preserve input order
public:
    Graph() : n(0), m(0) {}
    ~Graph() { clear(); }
    void clear()
    {
        for (auto h : head)
        {
            while (h)
            {
                AdjNode *t = h->next;
                delete h;
                h = t;
            }
        }
        head.clear();
        tail.clear();
        n = m = 0;
    }

    // Read graph from stream: first line contains n m, then m lines of edges u v (0-based)
    void readFromStream(std::istream &is)
    {
        clear();
        if (!(is >> n >> m))
            return;
        head.assign(n, nullptr);
        tail.assign(n, nullptr);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            is >> u >> v;
            if (u < 0 || u >= n || v < 0 || v >= n)
            {
                std::cerr << "Invalid edge: " << u << " " << v << "\n";
                continue;
            }
            // add v to u's list (append to preserve input order)
            AdjNode *a = new AdjNode(v);
            if (!head[u])
                head[u] = tail[u] = a;
            else
            {
                tail[u]->next = a;
                tail[u] = a;
            }
            // add u to v's list (undirected)
            AdjNode *b = new AdjNode(u);
            if (!head[v])
                head[v] = tail[v] = b;
            else
            {
                tail[v]->next = b;
                tail[v] = b;
            }
        }
    }

    void printAdjList() const
    {
        for (int i = 0; i < n; ++i)
        {
            std::cout << "Vertex " << i << ": ";
            AdjNode *p = head[i];
            while (p)
            {
                std::cout << "-> " << p->v << " ";
                p = p->next;
            }
            std::cout << "-> NULL\n";
        }
    }

    // Depth-first search starting from vertex `start` (0-based).
    // Returns the order of visited vertices.
    std::vector<int> dfs(int start) const
    {
        std::vector<int> order;
        if (start < 0 || start >= n)
            return order;
        std::vector<char> vis(n, 0);
        std::vector<int> stack;
        stack.push_back(start);
        while (!stack.empty())
        {
            int u = stack.back();
            stack.pop_back();
            if (vis[u])
                continue;
            vis[u] = 1;
            order.push_back(u);
            // push neighbors in reverse input order so that traversal
            // visits them in the same order as stored in the list
            std::vector<int> neigh;
            for (AdjNode *p = head[u]; p; p = p->next)
                neigh.push_back(p->v);
            for (auto it = neigh.rbegin(); it != neigh.rend(); ++it)
                stack.push_back(*it);
        }
        return order;
    }

    std:: vector<int> bfs(int start) const
    {
        std::vector<int> order;
        if (start < 0 || start >= n)
            return order;
        std::vector<char> vis(n, 0);
        std::vector<int> queue;
        queue.push_back(start);
        vis[start] = 1;
        size_t idx = 0;
        while (idx < queue.size())
        {
            int u = queue[idx++];
            order.push_back(u);
            for (AdjNode *p = head[u]; p; p = p->next)
            {
                int v = p->v;
                if (!vis[v])
                {
                    vis[v] = 1;
                    queue.push_back(v);
                }
            }
        }
        return order;
    }
};