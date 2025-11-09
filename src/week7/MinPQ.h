template <typename T>
class MinPQ
{
public:
    virtual ~MinPQ() {} // 虚析构函数

    virtual bool isEmpty() const = 0;       // 判断队列是否为空
    virtual int size() const = 0;           // 返回队列元素个数
    virtual const T &getMin() const = 0;    // 返回最小元素（不删除）
    virtual void insert(const T &item) = 0; // 插入元素
    virtual void removeMin() = 0;           // 删除最小元素
    virtual T extractMin() = 0;             // 删除并返回最小元素
};