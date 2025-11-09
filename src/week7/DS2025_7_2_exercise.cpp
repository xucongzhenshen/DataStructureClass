#include "InorderThreadedTree.h"
int main() {
    BinaryTree<int> bt;
    bt.insert(4);
    bt.insert(2);
    bt.insert(6);
    bt.insert(1);
    bt.insert(3);
    bt.insert(5);
    bt.insert(7);

    InorderThreadedTree<int> itt;
    itt.buildFromBinaryTree(bt);

    std::cout << "Inorder Traversal of Threaded Binary Tree: ";
    itt.inorderTraversal();
    std::cout << std::endl;
    InorderThreadedTree<int> itt2 = itt; // Test copy constructor
    std::cout << "Inorder Traversal of Copied Threaded Binary Tree: ";
    itt2.inorderTraversal();
    std::cout << std::endl;

    return 0;
}