/*
void D(int *x, int n)
{
    int i = 1;
    do {
        x[i] += 2;
        i += 2;
    } while (i <= n);

    i = 1;
    while (i <= n / 2) {
        x[i] += x[i + 1];
        i++;
    }
}
*/

#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n;
    // segment (a)
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    std::vector<int> x(n + 1);
    std::cout << "Enter " << n << " elements: ";
    for (int i = 1; i <= n; ++i)
        std::cin >> x[i];

    auto oringe = x; // store original input for later comparison

    int i = 1, count = 0;
    count ++;
    do
    {
        x[i] += 2;
        count++;
        i += 2;
        count++;
    } while (count++ && i <= n);

    i = 1;
    count++;

    while (count++ && i <= n / 2)
    {
        x[i] += x[i + 1];
        count++;
        i++;
        count++;
    }

    std::cout << "Processed elements: ";
    for (int i = 1; i <= n; ++i)
        std::cout << x[i] << " ";
    std::cout << "\nTotal operations: " << count << std::endl;

    std::cout << "----------------------------" << std::endl;
    // segment (b)
    x = oringe; // reset x to original input
    count = 0;

    i = 1;
    count ++;
    do
    {
        count+=3;
        x[i] += 2;
        i += 2;
    } while (i <= n);


    i = 1;
    count++;

    while (count++ && i <= n / 2)
    {
        count+=2;
        x[i] += x[i + 1];
        i++;
    }

    std::cout << "Processed elements: ";
    for (int i = 1; i <= n; ++i)
        std::cout << x[i] << " ";
    std::cout << "\nTotal operations: " << count << std::endl;

    count = 3 * (n + 1);
    std::cout << "Calculated operations: " << count << std::endl;
    return 0;
}
