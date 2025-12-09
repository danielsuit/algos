#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

// Huffman Coding: Optimal prefix-free encoding
// Time Complexity: O(n log n)
// Space Complexity: O(n)

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, const std::string& code, 
                   std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root) return;
    
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }
    
    generateCodes(root->left, code + \"0\", huffmanCodes);
    generateCodes(root->right, code + \"1\", huffmanCodes);
}

std::unordered_map<char, std::string> huffmanCoding(
    const std::unordered_map<char, int>& frequencies) {
    
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;
    
    for (const auto& [ch, freq] : frequencies) {
        minHeap.push(new Node(ch, freq));
    }
    
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        
        Node* merged = new Node('\\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        minHeap.push(merged);
    }
    
    Node* root = minHeap.top();
    std::unordered_map<char, std::string> huffmanCodes;
    generateCodes(root, \"\", huffmanCodes);
    
    return huffmanCodes;
}

int main() {
    std::cout << \"=== Huffman Coding ===\" << std::endl;
    std::cout << \"Time: O(n log n), Space: O(n)\" << std::endl << std::endl;
    
    std::unordered_map<char, int> freq = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };
    
    auto codes = huffmanCoding(freq);
    
    std::cout << \"Character frequencies and Huffman codes:\" << std::endl;
    for (const auto& [ch, f] : freq) {
        std::cout << \"  '\" << ch << \"': freq=\" << f << \", code=\" 
                 << codes[ch] << std::endl;
    }
    
    return 0;
}
