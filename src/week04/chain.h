#pragma once
#include <iostream>
class ChainNode
{
    friend class Chain;

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
    Chain() : head(nullptr) {}
    void insert(int val);
    void display();
    void deleteNode(ChainNode *node);
    ChainNode *operator[](int index);
    int compute();
};

void Chain::insert(int val)
{
    ChainNode *newNode = new ChainNode(val);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        ChainNode *temp = head;
        while (temp->link)
        {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}

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
