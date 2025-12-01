#include "chain.h"
Chain mergeChains(const Chain &chain1, const Chain &chain2){
    Chain mergedChain;
    ChainNode *ptr1 = chain1.head;
    ChainNode *ptr2 = chain2.head;
    ChainNode **lastPtrRef = &mergedChain.head;

    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (ptr1->data <= ptr2->data) {
            *lastPtrRef = new ChainNode(ptr1->data);
            ptr1 = ptr1->link;
        } else {
            *lastPtrRef = new ChainNode(ptr2->data);
            ptr2 = ptr2->link;
        }
        lastPtrRef = &((*lastPtrRef)->link);
    }

    while (ptr1 != nullptr) {
        *lastPtrRef = new ChainNode(ptr1->data);
        ptr1 = ptr1->link;
        lastPtrRef = &((*lastPtrRef)->link);
    }

    while (ptr2 != nullptr) {
        *lastPtrRef = new ChainNode(ptr2->data);
        ptr2 = ptr2->link;
        lastPtrRef = &((*lastPtrRef)->link);
    }

    return mergedChain;
}

int main()
{
    Chain chain1;
    chain1.insertAscending(1);
    chain1.insertAscending(3);
    chain1.insertAscending(5);

    Chain chain2;
    chain2.insertAscending(2);
    chain2.insertAscending(4);
    chain2.insertAscending(6);

    Chain mergedChain = mergeChains(chain1, chain2);
    mergedChain.display(); // Expected output: 1 2 3 4 5 6

    return 0;
}
