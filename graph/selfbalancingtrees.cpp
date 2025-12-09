#include <iostream>
#include <algorithm>

// Self-Balancing Trees: AVL Tree Implementation
// Time Complexity: O(log n) for insert, delete, search
// Space Complexity: O(n)

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    void updateHeight(AVLNode* node) {
        if (node)
            node->height = 1 + std::max(height(node->left), height(node->right));
    }
    
    // Right rotation
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    AVLNode* insert(AVLNode* node, int key) {
        // Standard BST insertion
        if (!node) return new AVLNode(key);
        
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // Duplicate keys not allowed
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        
        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    AVLNode* minValueNode(AVLNode* node) {
        while (node->left)
            node = node->left;
        return node;
    }
    
    AVLNode* deleteNode(AVLNode* node, int key) {
        if (!node) return node;
        
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            // Node with one child or no child
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                // Node with two children
                AVLNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }
        
        if (!node) return node;
        
        updateHeight(node);
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        
        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        
        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    void inorder(AVLNode* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->key << " ";
            inorder(node->right);
        }
    }
    
    void preorder(AVLNode* node) {
        if (node) {
            std::cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insert(root, key);
    }
    
    void remove(int key) {
        root = deleteNode(root, key);
    }
    
    void printInorder() {
        inorder(root);
        std::cout << std::endl;
    }
    
    void printPreorder() {
        preorder(root);
        std::cout << std::endl;
    }
    
    int getHeight() {
        return height(root);
    }
};

int main() {
    std::cout << "=== Self-Balancing Trees (AVL Tree) ===" << std::endl;
    std::cout << "Time: O(log n), Space: O(n)" << std::endl << std::endl;
    
    AVLTree tree;
    
    std::cout << "Inserting: 10, 20, 30, 40, 50, 25" << std::endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    
    std::cout << "Preorder traversal: ";
    tree.printPreorder();
    
    std::cout << "Inorder traversal: ";
    tree.printInorder();
    
    std::cout << "Tree height: " << tree.getHeight() << std::endl;
    
    std::cout << "\nDeleting 40" << std::endl;
    tree.remove(40);
    
    std::cout << "Preorder traversal: ";
    tree.printPreorder();
    
    std::cout << "\nAVL Tree Properties:" << std::endl;
    std::cout << "  - Balance factor: |height(left) - height(right)| <= 1" << std::endl;
    std::cout << "  - All operations: O(log n)" << std::endl;
    std::cout << "  - More rigid balancing than Red-Black trees" << std::endl;
    std::cout << "  - Better for lookup-intensive applications" << std::endl;
    
    std::cout << "\nOther Self-Balancing Trees:" << std::endl;
    std::cout << "  - Red-Black Tree: Less rigid balancing, faster insertion" << std::endl;
    std::cout << "  - Splay Tree: Recently accessed nodes near root" << std::endl;
    std::cout << "  - B-Tree: Multi-way tree for disk-based storage" << std::endl;
    
    return 0;
}
