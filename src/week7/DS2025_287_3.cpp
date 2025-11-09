#include "MinPQ.h"
#include <vector>
#include <iostream>

template <typename T>
class MinHeap : public MinPQ<T>
{
public:
    MinHeap() {}
    MinHeap(const std::vector<T>& items) : heap(items) {
        for (int i = parent(heap.size() - 1); i >= 0; --i) {
            int index = i;
            while (index < heap.size()) {
                int next = leftChild(index);
                if (next + 1 < heap.size() && heap[next] > heap[next + 1]) {
                    next++;
                }
                if (next < heap.size() && heap[index] > heap[next]) {
                    std::swap(heap[index], heap[next]);
                    index = next;
                } else {
                    break;
                }
            }
        }
    }
    MinHeap(const MinHeap &other) : heap(other.heap) {}
    MinHeap &operator=(const MinHeap &other){
        if (this != &other) {
            heap = other.heap;
        }
        return *this;
    }
    MinHeap &operator=(MinHeap &&other) noexcept {
        if (this != &other) {
            heap = std::move(other.heap);
        }
        return *this;
    }
    MinHeap(MinHeap &&other) noexcept : heap(std::move(other.heap)) {}
    virtual ~MinHeap() {}

    virtual bool isEmpty() const override {
        return heap.empty();
    }

    virtual int size() const override {
        return heap.size();
    }

    virtual const T& getMin() const override {
        if (!isEmpty()) {
            return heap.front();
        }
        throw std::runtime_error("Heap is empty");
    }

    void pop() {
        if (!isEmpty()) {
            heap.front() = heap.back();
            heap.pop_back();
            int index = 0;
            while (index < heap.size()) {
                int next = leftChild(index);
                if (next + 1 < heap.size() && heap[next] > heap[next + 1]) {
                    next++;
                }
                if (next < heap.size() && heap[index] > heap[next]) {
                    std::swap(heap[index], heap[next]);
                    index = next;
                } else {
                    break;
                }
            }
        }
    }

    void push(const T& item) {
        heap.push_back(item);
        int index = heap.size() - 1;
        while(index > 0) {
            int p = parent(index);
            if (heap[p] > heap[index]) {
                std::swap(heap[p], heap[index]);
                index = p;
            } else {
                break;
            }
        }
    }
    virtual void insert(const T& item) override {
        push(item);
    }

    virtual void removeMin() override {
        if (!isEmpty()) {
            pop();
        }
    }

    virtual T extractMin() override {
        if (!isEmpty()) {
            T minValue = heap.front();
            pop();
            return minValue;
        }
        throw std::runtime_error("Heap is empty");
    }

private:
    std::vector<T> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
};

int main() {
    MinHeap<int> minHeap;
    minHeap.insert(5);
    minHeap.insert(3);
    minHeap.insert(8);

    while (!minHeap.isEmpty()) {
        std::cout << minHeap.extractMin() << " ";
    }
    std::cout << std::endl;
    return 0;
}