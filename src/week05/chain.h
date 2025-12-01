#pragma once
#include <iostream>
class ChainNode
{
    friend class Chain;
    friend class TwoDirChain;
    friend Chain mergeChains(const Chain &chain1, const Chain &chain2);

public:
    ChainNode(int val) : data(val), link(nullptr) {}

private:
    ChainNode *link;
    int data;
};

class Chain
{
public:
    ChainNode *head;
    Chain() : head(nullptr) {};
    void insertAscending(int val);
    void display();
    void quickdeleteNode(ChainNode *node);
    ChainNode *operator[](int index);
    friend Chain mergeChains(const Chain &chain1, const Chain &chain2);
};

void Chain::display()
{
    ChainNode *temp = head;
    while (temp)
    {
        std::cout << temp->data << " ";
        temp = temp->link;
    }
    std::cout << std::endl;
}

ChainNode *Chain::operator[](int index)
{
    ChainNode *temp = head;
    int count = 0;
    while (temp)
    {
        if (count == index)
        {
            return temp;
        }
        temp = temp->link;
        count++;
    }
    return nullptr; // If index is out of bounds
}

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