#include <iostream>
#include "chain.h"
void Chain::insertAscending(int val)
{
    ChainNode *newNode = new ChainNode(val);
    if (!head || head->data >= val)
    {
        newNode->link = head;
        head = newNode;
        return;
    }
    ChainNode *current = head;
    while (current->link && current->link->data < val)
    {
        current = current->link;
    }
    newNode->link = current->link;
    current->link = newNode;
}

void Chain::quickdeleteNode(ChainNode *node)
{
    if (node == nullptr) return; // If node is nullptr, do nothing
    if (node == head)
    {
        // If the node to be deleted is the head node
        ChainNode *tempNode = head;
        head = head->link;
        delete tempNode;
        return;
    }
    else
    {
        int temp = node->data;
        node->data = head->data;
        head->data = temp;

        // Delete the head node
        ChainNode *tempNode = head;
        head = head->link;
        delete tempNode;
    }
    
}

// test
int main()
{
    Chain myChain;
    myChain.insertAscending(5);
    myChain.insertAscending(3);
    myChain.insertAscending(8);
    myChain.insertAscending(1);
    myChain.display(); // Expected output: 1 3 5 8

    ChainNode *nodeToDelete = myChain[2]; // Node with value 5
    myChain.quickdeleteNode(nodeToDelete);
    myChain.display(); // Expected output: 1 3 8

    return 0;
}

// Time complexity: O(n) in the worst case for insertion, O(1) for quick deletion