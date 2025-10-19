#include <iostream>

class ChainNode{
friend class Chain;
public:
    ChainNode(int val):data(val), link(nullptr){}
private:
    ChainNode* link;
    int data;
};

class Chain{
public:
    ChainNode* head;
    Chain():head(nullptr){}
    void insert(int val);
    void display();
    void deleteNode(ChainNode* node);
    ChainNode* operator[](int index);
};

void Chain::insert(int val) {
    ChainNode* newNode = new ChainNode(val);
    if (!head) {
        head = newNode;
    } else {
        ChainNode* temp = head;
        while (temp->link) {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}

void Chain::display() {
    ChainNode* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->link;
    }
    std::cout << std::endl;
}
void Chain::deleteNode(ChainNode* node) {
    if (!head || !node) return;

    if (head == node) {
        ChainNode* temp = head;
        head = head->link;
        delete temp;
        return;
    }

    ChainNode* temp = head;
    while (temp->link && temp->link != node) {
        temp = temp->link;
    }

    if (temp->link == node) {
        ChainNode* toDelete = temp->link;
        temp->link = toDelete->link;
        delete toDelete;
    }
}
ChainNode* Chain::operator[](int index) {
    ChainNode* temp = head;
    int count = 0;
    while (temp) {
        if (count == index) {
            return temp;
        }
        temp = temp->link;
        count++;
    }
    return nullptr; // If index is out of bounds
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