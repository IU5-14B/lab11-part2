#include "../include/avl_tree.h"
#include <iostream>
#include <algorithm>

// Return the height of a node; null nodes have height 0
int height(AVLNode* node) {
    return node ? node->height : 0;
}

// Compute the balance factor of a node
int getBalance(AVLNode* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

// Update the height of a node based on its children's heights
static void updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

// Perform a right rotation about y
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Perform a left rotation about x
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    // Return new root
    return y;
}

// Insert key into AVL tree
AVLNode* avlInsert(AVLNode* node, int key) {
    // Perform normal BST insertion
    if (node == nullptr)
        return new AVLNode(key);

    if (key < node->key)
        node->left = avlInsert(node->left, key);
    else if (key > node->key)
        node->right = avlInsert(node->right, key);
    else
        return node; // Duplicate keys are not inserted

    // Update this node's height
    updateHeight(node);

    // Check the balance factor to see if this node became unbalanced
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

    // Return unchanged node pointer
    return node;
}

// Print an inorder traversal
void inorder(AVLNode* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->key << " ";
    inorder(root->right);
}

// Delete the AVL tree recursively
void deleteTree(AVLNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}