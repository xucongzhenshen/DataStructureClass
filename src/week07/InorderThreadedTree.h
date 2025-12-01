#pragma once
#include <iostream>
#include "binaryTree.h"

template <typename T>
class InorderThreadedTree{
public:
    struct ThreadedNode {
        T data;
        ThreadedNode* left;
        ThreadedNode* right;
        bool isThreaded; // true if right pointer is a thread

        ThreadedNode(T val) : data(val), left(nullptr), right(nullptr), isThreaded(false) {};
    };

    ThreadedNode* root;

    InorderThreadedTree() : root(nullptr) {}
    InorderThreadedTree(const InorderThreadedTree& other){
        root = nullptr;
        
        if(other.root != nullptr){
            ThreadedNode* prev = nullptr;
            root = copy(other.root, root, prev);
        }
    }
    InorderThreadedTree& operator=(const InorderThreadedTree& other){
        if (this != &other) {
            recDestructor(root);
            root = nullptr;
            if(other.root != nullptr){
                ThreadedNode* prev = nullptr;
                root = copy(other.root, root, prev);
            }
        }
        return *this;
    }
    InorderThreadedTree(InorderThreadedTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }
    InorderThreadedTree& operator=(InorderThreadedTree&& other) noexcept {
        if (this != &other) {
            recDestructor(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }
    ~InorderThreadedTree() {
        recDestructor(root);
    }

    // Function to convert a binary tree to an inorder threaded binary tree
    void convertToThreaded(typename BinaryTree<T>::Node* btNode, ThreadedNode*& currentRoot, ThreadedNode*& prev) {
        if (btNode == nullptr) {
            return;
        }
        // Create a new threaded node
        currentRoot = new ThreadedNode(btNode->data);

        // Recursively convert the left subtree
        convertToThreaded(btNode->left, currentRoot->left, prev);
        // Link the previous node to the current node
        if (prev != nullptr) {
            if (prev->right == nullptr) {
                prev->right = currentRoot;
                prev->isThreaded = true;
            }
        }
        prev = currentRoot;
        // Recursively convert the right subtree
        convertToThreaded(btNode->right, currentRoot->right, prev);
    }

    void buildFromBinaryTree(BinaryTree<T>& bt) {
        ThreadedNode* prev = nullptr;
        convertToThreaded(bt.root, root, prev);
    }

    // Inorder traversal of the threaded binary tree
    void inorderTraversal() {
        ThreadedNode* current = root;
        // Find the leftmost node
        while (current && current->left != nullptr) {
            current = current->left;
        }

        while (current != nullptr) {
            std::cout << current->data << " ";

            // If this node is threaded, move to the inorder successor
            if (current->isThreaded) {
                current = current->right;
            } else {
                // Else move to the leftmost node in the right subtree
                current = current->right;
                while (current && current->left != nullptr) {
                    current = current->left;
                }
            }
        }
    }

    void recDestructor(ThreadedNode* node){
        if (node != nullptr) {
            if (!node->isThreaded) {
                recDestructor(node->right);
            }
            recDestructor(node->left);
            delete node;
        }
    }

    ThreadedNode *copy(
        const ThreadedNode *btNode,
        ThreadedNode *&currentRoot,
        ThreadedNode *&prev)
    {
        if (btNode == nullptr) {
            return nullptr;
        }
        ThreadedNode* newNode = new ThreadedNode(btNode->data);
        newNode->isThreaded = btNode->isThreaded;
        newNode->left = copy(btNode->left, newNode->left, prev);
        if (prev != nullptr && prev->isThreaded)
        {
            prev->right = newNode;
        }
        prev = newNode;
        if(!newNode->isThreaded) newNode->right = copy(btNode->right, newNode->right, prev);
        return std::move(newNode);
    }
};