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
    Chain() : head(nullptr) {};
    void insertAscending(int val);
    void display();
    void quickdeleteNode(ChainNode *node);
    ChainNode *operator[](int index);
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
