#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

class Huffman_Tree {
public:
    struct Node {
        char character;
        int frequency;
        Node* left;
        Node* right;

        Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    };

    Huffman_Tree();
    ~Huffman_Tree();

    void build(const std::vector<std::pair<char, int>>& char_freqs);
    std::string encode(const std::string& text);
    std::string decode(const std::string& binary_str);
private:
    Node* root;
    void deleteTree(Node* node);
    void generateCodes(Node* node, const std::string& prefix, std::unordered_map<char, std::string>& codes);
};
void Huffman_Tree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
Huffman_Tree::Huffman_Tree() : root(nullptr) {}

Huffman_Tree::~Huffman_Tree() {
    deleteTree(root);
}

void Huffman_Tree::generateCodes(Node* node, const std::string& prefix, std::unordered_map<char, std::string>& codes) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[node->character] = prefix;
    }
    generateCodes(node->left, prefix + "0", codes);
    generateCodes(node->right, prefix + "1", codes);
}

void Huffman_Tree::build(const std::vector<std::pair<char, int>>& char_freqs) {
    auto cmp = [](Node* left, Node* right) { return left->frequency > right->frequency; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> minHeap(cmp);

    for (const auto& cf : char_freqs) {
        minHeap.push(new Node(cf.first, cf.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* merged = new Node('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }

    root = minHeap.top();
}