#include "binaryTree.h"


// test
int main() {
    BinaryTree<int> bt;
    bt.insert(5);
    bt.insert(3);
    bt.insert(7);
    bt.insert(2);
    bt.insert(4);

    std::cout << "Inorder traversal: ";
    bt.inorder(); // Expected output: 2 3 4 5 7
    std::cout << std::endl;

    int searchVal = 4;
    if (bt.search(searchVal)) {
        std::cout << searchVal << " found in the tree." << std::endl;
    } else {
        std::cout << searchVal << " not found in the tree." << std::endl;
    }

    searchVal = 6;
    if (bt.search(searchVal)) {
        std::cout << searchVal << " found in the tree." << std::endl;
    } else {
        std::cout << searchVal << " not found in the tree." << std::endl;
    }

    return 0;
}
// Time complexity:
// recDestructor: O(n), where n is the number of nodes in the tree.