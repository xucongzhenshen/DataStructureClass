#include "binaryTree.h"
#include <iostream>
#include <random>
#include <fstream>
#include <omp.h> 

std::unique_ptr<int[]> randomShuffle(int n)
{
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(n);
    for (int i = 0; i < n; ++i)
    {
        arr[i] = i;
    }
    std::mt19937 rng{std::random_device{}()};
    for (int i = n - 1; i > 0; --i)
    {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rng);
        std::swap(arr[i], arr[j]);
    }
    return std::move(arr);
}

int main()
{
    const int trials = 20;
    auto filepath = "output_height.csv";
    std::ofstream outfile(filepath);
    const int test_n[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    outfile << "n,";
    for (int trial = 0; trial < trials; ++trial)
    {
        outfile << "trial" << trial + 1 << ",";
    }
    outfile << "average\n";

    for (int n : test_n)
    {
        std::vector<int> heights(trials); // 存储每次试验的高度

        // 并行处理 trials
        #pragma omp parallel for
        for (int trial = 0; trial < trials; ++trial)
        {
            // 每个线程有自己的随机数生成器
            std::unique_ptr<int[]> arr = randomShuffle(n);
            BinaryTree<int> tree;
            for (int i = 0; i < n; ++i)
            {
                tree.insert(arr[i]);
            }
            // Measure height
            int height = tree.height();
            heights[trial] = height;
        }

        // 输出结果
        outfile << n << ",";
        float sum_height = 0;
        for (int trial = 0; trial < trials; ++trial)
        {
            outfile << heights[trial] << ",";
            sum_height += heights[trial];
        }
        outfile << sum_height / trials << "\n";
    }

    outfile.close();
    std::cout << "Height data written to " << filepath << std::endl;
    return 0;
}