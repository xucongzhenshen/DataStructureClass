#include"binaryTree.h"
#include <iostream>
template<typename Element>
struct DataPair {
    int key;
    Element value;
    DataPair(int k, Element&& v) noexcept : key(k), value(std::move(v)) {}
    DataPair(const DataPair& other) : key(other.key), value(other.value) {}
    DataPair& operator=(const DataPair& other) {
        if (this != &other) {
            key = other.key;
            value = other.value;
        }
        return *this;
    }
};
template<typename Element>
bool operator>=(const DataPair<Element>& a, const DataPair<Element>& b) {
    return a.key >= b.key;
}
template<typename Element>
bool operator<=(const DataPair<Element>& a, const DataPair<Element>& b) {
    return a.key <= b.key;
}
template<typename Element>
bool operator==(const DataPair<Element>& a, const DataPair<Element>& b) {
    return a.key == b.key;
}
template<typename Element>
bool operator!=(const DataPair<Element>& a, const DataPair<Element>& b) {
    return a.key != b.key;
}
template<typename Element>
bool operator<(const DataPair<Element>& a, const DataPair<Element>& b) {
    return a.key < b.key;
}
template<typename Element>
bool operator>(const DataPair<Element>& a, const DataPair<Element>& b) {
    return a.key > b.key;
}
template<typename Element>
std::ostream& operator<<(std::ostream& os, const DataPair<Element>& dp) {
    os << "{" << dp.key << ", " << dp.value << "}";
    return os;
}

int main() {
    BinaryTree<DataPair<std::string>> bt;
    bt.insert({5, "five"});
    bt.insert({3, "three"});
    bt.insert({7, "seven"});
    bt.insert({2, "two"});
    bt.insert({4, "four"});

    std::cout << "Inorder traversal: ";
    bt.inorder(); // Expected output: 2 3 4 5 7
    std::cout << std::endl;

    DataPair<std::string> searchVal = {4, ""};
    if (bt.search(searchVal)) {
        std::cout << searchVal.key << " found in the tree." << std::endl;
    } else {
        std::cout << searchVal.key << " not found in the tree." << std::endl;
    }

    searchVal = DataPair<std::string>({6, ""});
    if (bt.search(searchVal)) {
        std::cout << searchVal.key << " found in the tree." << std::endl;
    } else {
        std::cout << searchVal.key << " not found in the tree." << std::endl;
    }

    return 0;
}