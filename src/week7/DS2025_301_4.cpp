#include <iostream>
#include <vector>
#include "LoserTree.h"

// 模拟多个有序序列
class MultiWayMerge
{
private:
    std::vector<std::vector<int>> sequences;
    std::vector<size_t> positions;

public:
    MultiWayMerge(const std::vector<std::vector<int>> &seqs)
        : sequences(seqs), positions(seqs.size(), 0) {}

    int getRecord(int sequenceIndex)
    {
        return sequences[sequenceIndex][positions[sequenceIndex]];
    }

    bool hasNext(int sequenceIndex)
    {
        return positions[sequenceIndex] < sequences[sequenceIndex].size();
    }

    void moveNext(int sequenceIndex)
    {
        if (hasNext(sequenceIndex))
        {
            positions[sequenceIndex]++;
        }
    }
};

int main()
{
    std::vector<std::vector<int>> sequences = {
        {1, 6, 11, 16},
        {2, 7, 12, 17},
        {3, 8, 13, 18},
        {4, 9, 14, 19},
        {5, 10, 15, 20},
    };

    MultiWayMerge merger(sequences);
    int k = sequences.size();

    // 创建败者树，使用函数对象获取记录
    LoserTree<int> tree(k, 
        [&merger](int idx)
        { return merger.getRecord(idx); },
        [&merger](int idx)
        { return merger.hasNext(idx); });

    std::cout << "Multi-way merge result: ";
    while (!tree.isEmpty())
    {
        // 输出当前最小值
        std::cout << tree.getMin() << " ";

        // 移动到获胜序列的下一个元素
        int winner = tree.getWinnerIndex();
        merger.moveNext(winner);

        // 更新败者树
        tree.next();
    }
    std::cout << std::endl;

    return 0;
}