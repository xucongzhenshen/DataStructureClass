// The concrete iterator class is in file binaryTree.h
// This is just to show the usage of the iterator in the binary tree class
#include "binaryTree.h"
#include <string>

int main() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "Inorder traversal: ";
    for (auto it = tree.begin("inorder"); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    for (auto it = tree.begin("preorder"); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    for (auto it = tree.begin("postorder"); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}