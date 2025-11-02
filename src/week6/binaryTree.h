#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <utility>
template <typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T val) : data(val), left(nullptr), right(nullptr) {};
        friend ostream& operator<<(ostream &os, const Node &node) {
            os << node.data << '\t';
            return os;
        };
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
    
    void recDestructor(Node* node);

};
// Simple forward iterator for BinaryTree::Node
template <typename NodeT>
class MyForwardIterator {
    std::string mode;
    NodeT* current;
    // stacks used by iterative algorithms
    std::vector<NodeT*> st_nodes;                 // for inorder/preorder
    std::vector<std::pair<NodeT*, bool>> st_flags; // for postorder

    // pointer used while traversing inorder
    NodeT* cur_ptr = nullptr;

    void advanceInorder() {
        while (cur_ptr) {
            st_nodes.push_back(cur_ptr);
            cur_ptr = cur_ptr->left;
        }
        if (st_nodes.empty()) { current = nullptr; return; }
        current = st_nodes.back(); st_nodes.pop_back();
        cur_ptr = current->right;
    }

    void advancePreorder() {
        if (st_nodes.empty()) { current = nullptr; return; }
        current = st_nodes.back(); st_nodes.pop_back();
        if (current->right) st_nodes.push_back(current->right);
        if (current->left) st_nodes.push_back(current->left);
    }

    void advancePostorder() {
        while (!st_flags.empty()) {
            auto &p = st_flags.back();
            if (!p.second) {
                p.second = true;
                if (p.first->right) st_flags.push_back({p.first->right, false});
                if (p.first->left) st_flags.push_back({p.first->left, false});
            } else {
                current = p.first; st_flags.pop_back(); return;
            }
        }
        current = nullptr;
    }

public:
    MyForwardIterator(NodeT* root, const std::string &m) : mode(m), current(nullptr), cur_ptr(nullptr) {
        if (!root) { current = nullptr; return; }
        if (mode == "inorder") { cur_ptr = root; advanceInorder(); }
        else if (mode == "preorder") { st_nodes.clear(); st_nodes.push_back(root); advancePreorder(); }
        else if (mode == "postorder") { st_flags.clear(); st_flags.push_back({root, false}); advancePostorder(); }
        else current = nullptr;
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