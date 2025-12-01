#include "union.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <utility>
#include <random>

std::pair<int, int> randomGenerate(int n, int /*ignore*/)
{
    if(n < 2)
    {
        throw std::invalid_argument("n must be at least 2 to generate a pair of distinct elements.");
    }
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, n - 1);
    int a = dist(rng);
    int b = dist(rng);
    if(a == b)
    {
        b = (b + 1) % n;
    }
    return std::make_pair(a, b);
}
// 链式连接 - 更容易产生高树
std::pair<int, int> chainGenerate(int n, int i)
{
    return std::make_pair(i, (i + 1) % n);
}

// 星型连接
std::pair<int, int> starGenerate(int n, int /*ignore*/)
{
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(1, n - 1);
    return std::make_pair(dist(rng), 0);
}

auto test(
    int unionSize, 
    bool weighted, 
    int testNum, 
    std::pair<int, int> (*generateFunc)(int, int), 
    int iterations = -1)
{
    if(iterations == -1)
    {
        iterations = unionSize / 2;
    }
    std::string U_s,f_s;
    if(weighted)
    {
        std::cout << "Testing Union-Find with Union by Rank and Path Compression:" << std::endl;
        for(int k = 0; k < testNum; ++k)
        {
            Set uf(unionSize);
            auto start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < iterations; ++i)
            {
                
                auto pair = generateFunc(unionSize, i);
                uf.weightedUnion(uf.collapsingFind(pair.first), uf.collapsingFind(pair.second));
                
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> union_elapsed = end - start;

            start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < iterations; ++i)
            {
                auto pair = generateFunc(unionSize, i);
                uf.collapsingFind(pair.first);
                uf.collapsingFind(pair.second);
            }
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> find_elapsed = (end - start)/iterations;
            
            U_s += std::to_string(unionSize) + "," + "1" + "," + std::to_string(k + 1) + "," + std::to_string(union_elapsed.count()) + "\n";
            f_s += std::to_string(unionSize) + "," + "1" + "," + std::to_string(k + 1) + "," + std::to_string(find_elapsed.count()) + "\n";
        }
    }
    else
    {
        std::cout << "Testing Union-Find without optimizations:" << std::endl;
        for(int k = 0; k < testNum; ++k)
        {
            Set uf(unionSize);
            auto start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < unionSize / 2; ++i)
            {
                
                auto pair = generateFunc(unionSize, i);
                uf.simpleUnion(uf.simpleFind(pair.first), uf.simpleFind(pair.second));
                
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> union_elapsed = end - start;

            start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < iterations; ++i)
            {
                auto pair = generateFunc(unionSize, i);
                uf.simpleFind(pair.first);
                uf.simpleFind(pair.second);
            }
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> find_elapsed = (end - start)/iterations;

            U_s += std::to_string(unionSize) + "," + "0" + "," + std::to_string(k + 1) + "," + std::to_string(union_elapsed.count()) + "\n";
            f_s += std::to_string(unionSize) + "," + "0" + "," + std::to_string(k + 1) + "," + std::to_string(find_elapsed.count()) + "\n";
        }
    }
    return std::make_pair(U_s, f_s);
}


int main()
{
    const int testNum = 50;
    std::string r_filename = "src/week8/data/random_union_results.csv";
    std::string c_filename = "src/week8/data/chain_union_results.csv";
    std::string s_filename = "src/week8/data/star_union_results.csv";
    std::string r_f_filename = "src/week8/data/random_find_results.csv";
    std::string c_f_filename = "src/week8/data/chain_find_results.csv";
    std::string s_f_filename = "src/week8/data/star_find_results.csv";
    std::ofstream r_file(r_filename);
    if (!r_file.is_open())
    {
        std::cerr << "Failed to open file: " << r_filename << std::endl;
        return 1;
    }
    r_file << "UnionSize,Weighted,TestNum,Time" << std::endl;

    std::ofstream c_file(c_filename);
    if (!c_file.is_open())
    {
        std::cerr << "Failed to open file: " << c_filename << std::endl;
        return 1;
    }
    c_file << "UnionSize,Weighted,TestNum,Time" << std::endl;
    std::ofstream s_file(s_filename);
    if (!s_file.is_open())
    {
        std::cerr << "Failed to open file: " << s_filename << std::endl;
        return 1;
    }
    s_file << "UnionSize,Weighted,TestNum,Time" << std::endl;
    std::ofstream r_f_file(r_f_filename);
    if (!r_f_file.is_open())
    {
        std::cerr << "Failed to open file: " << r_f_filename << std::endl;
        return 1;
    }
    r_f_file << "UnionSize,Weighted,TestNum,Time" << std::endl;
    std::ofstream c_f_file(c_f_filename);
    if (!c_f_file.is_open())
    {
        std::cerr << "Failed to open file: " << c_f_filename << std::endl;
        return 1;
    }
    c_f_file << "UnionSize,Weighted,TestNum,Time" << std::endl;
    std::ofstream s_f_file(s_f_filename);
    if (!s_f_file.is_open())
    {
        std::cerr << "Failed to open file: " << s_f_filename << std::endl;
        return 1;
    }
    s_f_file << "UnionSize,Weighted,TestNum,Time" << std::endl;
    
#pragma omp parallel for 
    for (int n = 5000; n <= 50000; n += 5000)
    {
        std::pair<std::string, std::string> random_testResult = test(n, true, testNum, randomGenerate);
        std::string random_unionResult, random_findResult;
        random_unionResult += random_testResult.first;
        random_findResult += random_testResult.second;

        std::pair<std::string, std::string> random_testResult_unweighted = test(n, false, testNum, randomGenerate);
        random_unionResult += random_testResult_unweighted.first;
        random_findResult += random_testResult_unweighted.second;

        std::pair<std::string, std::string> chain_testResult = test(n, true, testNum, chainGenerate);
        std::string chain_unionResult, chain_findResult;
        chain_unionResult += chain_testResult.first;
        chain_findResult += chain_testResult.second;

        std::pair<std::string, std::string> chain_testResult_unweighted = test(n, false, testNum, chainGenerate);
        chain_unionResult += chain_testResult_unweighted.first;
        chain_findResult += chain_testResult_unweighted.second;

        std::pair<std::string, std::string> star_testResult =  test(n, true, testNum, starGenerate);
        std::string star_unionResult, star_findResult;
        star_unionResult += star_testResult.first;
        star_findResult += star_testResult.second;

        std::pair<std::string, std::string> star_testResult_unweighted =  test(n, false, testNum, starGenerate);
        star_unionResult += star_testResult_unweighted.first;
        star_findResult += star_testResult_unweighted.second;
#pragma omp critical
        {
            r_file << random_unionResult;
            r_f_file << random_findResult;
            c_file << chain_unionResult;
            c_f_file << chain_findResult;
            s_file << star_unionResult;
            s_f_file << star_findResult;
            std::cout << "Completed tests for union size: " << n << std::endl;
        }
    }
    // Set w_uf(10000), u_uf(10000);
    // for(int i = 0; i < 5000; ++i)
    // {
    //     auto pair = chainGenerate(10000, i);
    //     w_uf.weightedUnion(w_uf.collapsingFind(pair.first), w_uf.collapsingFind(pair.second));
    //     u_uf.simpleUnion(u_uf.simpleFind(pair.first), u_uf.simpleFind(pair.second));
    // }
    // std::cout << "Weighted Union-Find Stats:" << std::endl;
    // w_uf.printStats();
    // std::cout << "Unweighted Union-Find Stats:" << std::endl;
    // u_uf.printStats();
    return 0;
}