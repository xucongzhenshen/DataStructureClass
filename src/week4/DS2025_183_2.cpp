#include <iostream>
#include "chain.h"

void Chain::deleteNode(ChainNode *node)
{
    if (!head || !node)
        return;

    if (head == node)
    {
        ChainNode *temp = head;
        head = head->link;
        delete temp;
        return;
    }

    ChainNode *temp = head;
    while (temp->link && temp->link != node)
    {
        temp = temp->link;
    }

    if (temp->link == node)
    {
        ChainNode *toDelete = temp->link;
        temp->link = toDelete->link;
        delete toDelete;
    }
}

int main() {
    Chain chain;
    chain.insert(10);
    chain.insert(20);
    chain.insert(30);
    chain.display();

    ChainNode* nodeToDelete = chain[1]; // Deleting the second node (20)
    chain.deleteNode(nodeToDelete);
    chain.display();

    return 0;
}

// Time Complexity: O(n)