#include "chain.h"
class TwoDirChain{
private:
    ChainNode* r;
    ChainNode* l;
public:
    TwoDirChain(): r(nullptr), l(nullptr) {}
    void insertAtRight(int val){
        ChainNode* newNode = new ChainNode(val);
        newNode->link = r;
        r = newNode;
    }
    void insertAtLeft(int val){
        ChainNode* newNode = new ChainNode(val);
        newNode->link = l;
        l = newNode;
    }
    void insertAtRightHead(ChainNode* newNode)
    {
        newNode->link = r;
        r = newNode;
    }
    void insertAtLeftHead(ChainNode* newNode)
    {
        newNode->link = l;
        l = newNode;
    }
    void rightTraverse(int n){
        ChainNode* temp = r;
        while(temp && n){
            r = r->link;
            insertAtLeftHead(temp);
            temp = r;
            n--;
        }
    }
    void leftTraverse(int n){
        ChainNode* temp = l;
        while(temp && n){
            l = l->link;
            insertAtRightHead(temp);
            temp = l;
            n--;
        }
    }   
    ChainNode* getRightHead(){
        if(!r) std::cerr<< "Right chain is empty!" << std::endl;
        return r;
    }
    void printChain(){
        ChainNode* temp = r;
        if(!r){
            std::cout << "Right Chain is empty!" << std::endl;
        }
        else{
            std::cout << "Right Chain: ";
            while (temp)
            {
                std::cout << temp->data << " ";
                temp = temp->link;
            }
            std::cout << std::endl;
        }
        
        temp = l;
        if(!l){
            std::cout << "Left Chain is empty!" << std::endl;
            return;
        }
        std::cout << "Left Chain: ";
        while(temp){
            std::cout << temp->data << " ";
            temp = temp->link;
        }
        std::cout << std::endl;
    }
    ~TwoDirChain(){
        while(r){
            ChainNode* temp = r;
            r = r->link;
            delete temp;
        }
        while(l){
            ChainNode* temp = l;
            l = l->link;
            delete temp;
        }
    }
};

int main(){
    TwoDirChain tdc;
    tdc.insertAtRight(1);
    tdc.insertAtRight(2);
    tdc.insertAtRight(3);
    tdc.insertAtRight(4);
    tdc.insertAtRight(5);
    tdc.rightTraverse(2);
    tdc.printChain();
    tdc.leftTraverse(2);
    tdc.printChain();
    return 0;
}