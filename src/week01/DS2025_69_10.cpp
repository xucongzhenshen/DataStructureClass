#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;

int BinarySearch(int *a, const int x, const int n)
{ // Search the sorted array a [0], ... , a [n-1] for x.
    int left = 0, right = n - 1;
    while (left <= right)
    { // there are more elements
        int middle = (left + right) / 2;
        if (x < a[middle])
            right = middle - 1;
        else if (x > a[middle])
            left = middle + 1;
        else
            return middle;
    } // end of while
    return -1; // not found
}

void RunExperiment(string filepath)
{
    ofstream file(filepath);
    if (file.is_open())
    {
        file << "n,average_time(ns)\n";
    }
    else
    {
        cerr << "Failed to open file: " << filepath << endl;
        return;
    }

    for (int n = 2; n <= 100; n += 2)
    {
        // create an array containing [0, 1, 2, ..., n-1]
        int *arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = i;
        }

        double totalTime = 0.0;
        int repetitions = 5000; // repeat the search multiple times for averaging

        for (int rep = 0; rep < repetitions; rep++)
        {
            // search for all elements from 0 to n-1
            for (int target = 0; target < n; target++)
            {
                auto start = std::chrono::high_resolution_clock::now();

                BinarySearch(arr, target, n);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                totalTime += duration.count();
            }
        }

        double averageTime = totalTime / (n * repetitions);
        // write results to file
        file << n << "," << averageTime << "\n";
        cout << "n: " << n << ", average_time: " << averageTime << " ns" << endl;

        delete[] arr;
    }
}
int main()
{
    RunExperiment("data/runtime.csv");
    return 0;
}