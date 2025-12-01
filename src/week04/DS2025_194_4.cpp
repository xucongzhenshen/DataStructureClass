#include <iostream>
#include "chain.h"

int Chain::compute() {
    int sum = 0;
    ChainNode *iter1 = head;
    ChainNode *iter2 = (*this)[5]; // Example: get the 6th node
    if(iter2 == nullptr) {
        return sum; // If the 6th node doesn't exist, return 0
    }
    while (iter1 && iter2) {
        sum += iter1->data * iter2->data;
        iter1 = iter1->link;
        iter2 = iter2->link;
    }
    return sum;
}

int main() {
    Chain chain;
    chain.insert(10);
    chain.insert(20);
    chain.insert(30);
    chain.insert(40);
    chain.insert(50);
    chain.insert(60);
    chain.insert(70);
    chain.display();

    int result = chain.compute();
    std::cout << "Compute result: " << result << std::endl;
    chain.display();

    return 0;
}