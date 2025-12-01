#include <iostream>
#include <vector>
#include <string>

// Function to compare two lists lexicographically
int compareLists(const std::vector<int> &a, const std::vector<int> &b)
{
    size_t minSize = std::min(a.size(), b.size());
    for (size_t i = 0; i < minSize; ++i)
    {
        if (a[i] < b[i])
            return -1;
        if (a[i] > b[i])
            return 1;
    }
    if (a.size() < b.size())
        return -1;
    if (a.size() > b.size())
        return 1;
    return 0;
}

int main()
{
    std::vector<int> a, b;
    int num;

    a = {1, 2, 3, 5, 7};
    b = {1, 2, 3};
    int result = compareLists(a, b);
    if (result == -1)
    {
        std::cout << "a < b\n";
    }
    else if (result == 1)
    {
        std::cout << "a > b\n";
    }
    else
    {
        std::cout << "a == b\n";
    }

    return 0;
}