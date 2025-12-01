#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>

template <typename T>
class LoserTree
{
public:
    // 构造函数：用k个记录构建败者树
    LoserTree(const std::vector<T> &elements);

    // 多路归并专用构造函数：接受比较函数
    LoserTree(int k, std::function<T(int)> getRecord, std::function<bool(int)> hasNext);

    // 拷贝和移动构造函数
    LoserTree(const LoserTree &other) = default;
    LoserTree &operator=(const LoserTree &other) = default;
    LoserTree(LoserTree &&other) noexcept = default;
    LoserTree &operator=(LoserTree &&other) noexcept = default;
    ~LoserTree() = default;

    // 基本查询接口
    const T &getMin() const;    // 返回当前最小元素
    int getWinnerIndex() const; // 返回获胜者索引
    bool isEmpty() const;       // 判断树是否为空
    int size() const;           // 返回外部结点数量

    // 关键接口：处理外部结点变化
    void replay();                                     // 重新调整整个败者树
    void replay(int changedIndex);                     // 当指定外部结点值变化时重新调整
    void updateExternal(int index, const T &newValue); // 更新外部结点值并调整

    // 多路归并专用接口
    bool next();                               // 移动到下一个元素（多路归并用）
    bool isSequenceExhausted(int index) const; // 检查序列是否耗尽

private:
    std::vector<int> tree;        // 败者树存储索引
    std::vector<T> externalNodes; // 外部结点当前值
    std::vector<bool> active;     // 标记哪些外部结点仍然有效

    // 多路归并专用成员
    std::function<T(int)> getNextRecord;    // 获取下一个记录的函数
    std::function<bool(int)> hasNextRecord; // 检查是否有下一个记录的函数

    // 辅助函数
    int parent(int index) const
    {
        return (index + externalNodes.size()) / 2;
    }

    void buildTree();            // 构建败者树
    void adjust(int startIndex); // 从指定位置开始调整
};

// 构造函数1：直接使用给定的元素向量
template <typename T>
LoserTree<T>::LoserTree(const std::vector<T> &elements)
    : externalNodes(elements), active(elements.size(), true)
{
    buildTree();
}

// 构造函数2：多路归并专用，使用回调函数获取记录
template <typename T>
LoserTree<T>::LoserTree(int k,
                        std::function<T(int)> getRecord,
                        std::function<bool(int)> hasNext)
    : getNextRecord(getRecord), hasNextRecord(hasNext)
{

    externalNodes.resize(k);
    active.resize(k, true);
    tree.resize(k, -1);

    // 初始化外部结点
    for (int i = 0; i < k; ++i)
    {
        if (hasNextRecord(i))
        {
            externalNodes[i] = getNextRecord(i);
        }
        else
        {
            externalNodes[i] = T(); // 或者使用最大值表示序列耗尽
            active[i] = false;
        }
    }

    buildTree();
}

// 构建败者树
template <typename T>
void LoserTree<T>::buildTree()
{
    int k = externalNodes.size();
    std::fill(tree.begin(), tree.end(), -1);

    for (int i = k - 1; i >= 0; --i)
    {
        if (active[i])
        {
            adjust(i);
        }
    }
}

// 调整败者树
template <typename T>
void LoserTree<T>::adjust(int startIndex)
{
    int current = startIndex;
    int p = parent(current);

    while (p > 0)
    {
        if (tree[p] == -1)
        {
            // 第一次访问这个内部结点
            tree[p] = current;
            break;
        }
        if (externalNodes[current] > externalNodes[tree[p]])
        {
            std::swap(current, tree[p]);
        }
        p /= 2;
    }
    tree[0] = current; // 最终获胜者放在根节点    
}

// 基本查询接口
template <typename T>
const T &LoserTree<T>::getMin() const
{
    if (isEmpty())
    {
        throw std::runtime_error("LoserTree is empty");
    }
    return externalNodes[tree[0]];
}

template <typename T>
int LoserTree<T>::getWinnerIndex() const
{
    if (isEmpty())
    {
        throw std::runtime_error("LoserTree is empty");
    }
    return tree[0];
}

template <typename T>
bool LoserTree<T>::isEmpty() const
{
    for (bool a : active)
    {
        if (a)
            return false;
    }
    return true;
}

template <typename T>
int LoserTree<T>::size() const
{
    return externalNodes.size();
}

// 关键接口：处理外部结点变化
template <typename T>
void LoserTree<T>::replay()
{
    buildTree(); // 完全重建
}

template <typename T>
void LoserTree<T>::replay(int changedIndex)
{
    if (changedIndex >= 0 && changedIndex < externalNodes.size() && active[changedIndex])
    {
        adjust(changedIndex);
    }
}

template <typename T>
void LoserTree<T>::updateExternal(int index, const T &newValue)
{
    if (index >= 0 && index < externalNodes.size())
    {
        externalNodes[index] = newValue;
        if (newValue == T() || !active[index])
        { // 根据你的语义判断是否active
            active[index] = false;
        }
        else
        {
            active[index] = true;
        }
        replay(index);
    }
}

// 多路归并专用接口
template <typename T>
bool LoserTree<T>::next()
{
    if (isEmpty())
        return false;

    int winnerIndex = tree[0];

    if (hasNextRecord && hasNextRecord(winnerIndex))
    {
        // 获取下一个记录
        externalNodes[winnerIndex] = getNextRecord(winnerIndex);
        replay(winnerIndex);
        return true;
    }
    else
    {
        // 序列耗尽，标记为不活跃
        active[winnerIndex] = false;
        externalNodes[winnerIndex] = T(); // 或最大值

        // 重新调整败者树，排除这个序列
        buildTree();
        return !isEmpty();
    }
}

template <typename T>
bool LoserTree<T>::isSequenceExhausted(int index) const
{
    return !active[index];
}