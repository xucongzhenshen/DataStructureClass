#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <utility>
template <typename T>
class InorderThreadedTree;

template <typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T val) : data(val), left(nullptr), right(nullptr) {};
    };
    // iterator declared below

    BinaryTree() : root(nullptr) {}
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree(BinaryTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }
    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            recDestructor(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }
    ~BinaryTree() {
        recDestructor(root);
    }

    void insert(T val) {
        root = insertRec(root, val);
    }

    bool search(T val) {
        return searchRec(root, val);
    }

    void inorder() {
        inorderRec(root);
    }

    auto begin(const std::string& mode) {
        return MyForwardIterator<Node>(root, mode);
    }
    auto end() {
        return MyForwardIterator<Node>(nullptr, "");
    }

    int &height()
    {
        int height = 0;
        return measureHeight(height, root);
    }
    private:
    Node* root;

    Node* insertRec(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insertRec(node->left, val);
        } else {
            node->right = insertRec(node->right, val);
        }
        return node;
    }

    bool searchRec(Node* node, T val) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == val) {
            return true;
        }
        return val < node->data ? searchRec(node->left, val) : searchRec(node->right, val);
    }

    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
    }
    
    void recDestructor(Node* node){
        if (node != nullptr) {
            recDestructor(node->left);
            recDestructor(node->right);
            delete node;
        }
    }
    int &measureHeight(int &height, Node *node)
    {
        if (node == nullptr)
        {
            return height;
        }
        height++;
        int leftHeight = height;
        int rightHeight = height;
        measureHeight(leftHeight, node->left);
        measureHeight(rightHeight, node->right);
        height = std::max(leftHeight, rightHeight);
        return height;
    }
    friend class InorderThreadedTree<T>;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const typename BinaryTree<T>::Node& node) {
    os << node.data << " ";
    return os;
}

// Simple forward iterator for BinaryTree::Node
template <typename NodeT>
class MyForwardIterator {
    const std::string mode;
    NodeT *current;
    std::stack<std::pair<NodeT *, bool>> stk; // 使用std::stack

    // pointer used while traversing inorder
    NodeT* cur_ptr = nullptr;

    void advanceInorder() {
        while (cur_ptr != nullptr || !stk.empty()) {
            while (cur_ptr != nullptr) {
                stk.push({cur_ptr, false});
                cur_ptr = cur_ptr->left;
            }
            auto &p = stk.top();
            if (!p.second) {
                p.second = true;
                current = p.first;
                cur_ptr = p.first->right;
                stk.pop();
                return;
            }
        }
        current = nullptr;
    }

    void advancePreorder() {
        if (stk.empty()) { current = nullptr; return; }
        current = stk.top().first; stk.pop();
        if (current->right) stk.push(std::make_pair(current->right, false));
        if (current->left) stk.push(std::make_pair(current->left, false));
    }

    void advancePostorder() {
        while (!stk.empty()) {
            auto &p = stk.top();
            if (!p.second) {
                p.second = true;
                if (p.first->right) stk.push(std::make_pair(p.first->right, false));
                if (p.first->left) stk.push(std::make_pair(p.first->left, false));
            } else {
                current = p.first; stk.pop(); return;
            }
        }
        current = nullptr;
    }

public:
    MyForwardIterator(NodeT* root, const std::string &m) : mode(m), current(nullptr), cur_ptr(nullptr) {
        if (!root) { current = nullptr; return; }
        if (mode == "inorder") {
            cur_ptr = root;
            advanceInorder();
        } else if (mode == "preorder") {
            stk.push(std::make_pair(root, false));
            advancePreorder();
        } else if (mode == "postorder") {
            stk.push(std::make_pair(root, false));
            advancePostorder();
        } else {
            current = nullptr;
        }
    }

    MyForwardIterator() : mode(""), current(nullptr), cur_ptr(nullptr) {}

    MyForwardIterator& operator++() {
        if (mode == "inorder") advanceInorder();
        else if (mode == "preorder") advancePreorder();
        else if (mode == "postorder") advancePostorder();
        return *this;
    }

    bool operator!=(const MyForwardIterator& other) const { return current != other.current; }

    // return reference to data stored in the node
    auto operator*() const -> const decltype(current->data)& { return current->data; }
};