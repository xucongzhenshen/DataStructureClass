#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

template <class T>
void Insert(T temp, T a[], int i)
{
    while (i >= 1 && a[i] > temp)
    {
        a[i + 1] = a[i]; 
        i--;
    }
    a[i + 1] = temp; 
}

// 插入排序函数（与Program 7.5一致）
template <class T>
void InsertionSort(T a[], const int n)
{
    // 对a[1:n]进行非递减排序
    for (int j = 2; j <= n; j++)
    {
        T temp = a[j];
        Insert(temp, a, j - 1);

        // 输出每次迭代后的列表状态
        std::string label = "迭代 " + to_string(j - 1) + " 后";
        printArray(a, n, label);
    }
}

// 辅助函数：输出数组
template <class T>
void printArray(T a[], int n, const string &label)
{
    cout << label << ": ";
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    // 给定列表: (12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18)
    // 注意：数组索引从1开始，符合Program 7.5的描述
    const int n = 11;
    int arr[n + 1] = {0, 12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18}; // arr[0]不使用

    cout << "插入排序过程演示" << endl;
    cout << "初始列表: ";
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl
         << endl;

    // 执行插入排序
    InsertionSort(arr, n);

    cout << endl
         << "最终排序结果: ";
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 验证排序结果的正确性
    cout << endl
         << "验证: ";
    bool sorted = true;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            sorted = false;
            break;
        }
    }
    if (sorted)
    {
        cout << "列表已正确排序！" << endl;
    }
    else
    {
        cout << "排序错误！" << endl;
    }

    return 0;
}