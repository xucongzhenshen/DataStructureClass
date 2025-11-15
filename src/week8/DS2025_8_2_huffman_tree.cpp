#include "Huffman_Tree.h"
#include <iostream>

std::string Huffman_Tree::encode(const std::string& text) {
    std::unordered_map<char, std::string> codes;
    generateCodes(root, "", codes);

    std::string encoded_str;
    for (char ch : text) {
        encoded_str += codes[ch];
    }
    return encoded_str;
}
std::string Huffman_Tree::decode(const std::string& binary_str) {
    std::string decoded_str;
    Node* current = root;
    for (char bit : binary_str) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decoded_str += current->character;
            current = root;
        }
    }
    return decoded_str;
}

int main() {
    Huffman_Tree huffman;
    std::vector<std::pair<char, int>> char_freqs = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };
    huffman.build(char_freqs);

    std::string text = "abcdef";
    for(char ch : text) {
        std::cout << ch << "->" << huffman.encode(std::string(1, ch)) << std::endl;
    }
    std::cout << std::endl;
    std::string encoded = huffman.encode(text);
    std::cout << "Encoded: " << encoded << std::endl;
    std::string decoded = huffman.decode(encoded);
    std::cout << "Decoded: " << decoded << std::endl;
}