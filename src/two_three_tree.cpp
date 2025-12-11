#include "../include/two_three_tree.h"
#include <iostream>
#include <algorithm>

// A helper structure used during insertion to propagate splits up the tree
struct InsertResult {
    bool hasPromoted;      ///< whether a key was promoted to the parent
    int promotedKey;       ///< the key that moved up to the parent
    Node23* rightChild;    ///< the right child created after a split
    InsertResult() : hasPromoted(false), promotedKey(0), rightChild(nullptr) {}
};

/**
 * Recursively insert a key into the subtree rooted at node.  Returns a
 * structure describing whether a split occurred.  This helper performs
 * post‑order splitting: it only splits when a node actually overflows
 * after insertion.
 */
static InsertResult insertInternal(Node23* node, int key) {
    InsertResult res;
    // If this node is a leaf, insert the key here
    if (node->isLeaf()) {
        // Insert the key in sorted order
        node->keys.insert(std::upper_bound(node->keys.begin(), node->keys.end(), key), key);
        // If the node now has three keys, we need to split
        if (node->keys.size() == 3) {
            // keys are sorted; median is at index 1
            int median = node->keys[1];
            Node23* right = new Node23();
            // right node gets the largest key
            right->keys.push_back(node->keys[2]);
            // left node (current) keeps the smallest key
            node->keys.erase(node->keys.begin() + 1, node->keys.end());
            res.hasPromoted = true;
            res.promotedKey = median;
            res.rightChild = right;
        }
        return res;
    }

    // Non‑leaf: determine which child to descend into
    size_t i = 0;
    if (node->keys.size() == 1) {
        if (key < node->keys[0]) i = 0;
        else i = 1;
    } else { // size == 2
        if (key < node->keys[0]) i = 0;
        else if (key < node->keys[1]) i = 1;
        else i = 2;
    }
    // Recurse into the chosen child
    InsertResult childRes = insertInternal(node->children[i], key);
    if (childRes.hasPromoted) {
        // Insert promoted key into this node
        node->keys.insert(node->keys.begin() + i, childRes.promotedKey);
        // Insert new right child into children at position i+1
        node->children.insert(node->children.begin() + i + 1, childRes.rightChild);
        // If the node overflows, split it
        if (node->keys.size() == 3) {
            int median = node->keys[1];
            // Create new right node
            Node23* right = new Node23();
            // Move the largest key to the right node
            right->keys.push_back(node->keys[2]);
            // Move appropriate children to the right node
            // Children count for a node with 3 keys is 4; we need to move the last two children
            right->children.push_back(node->children[2]);
            right->children.push_back(node->children[3]);
            // Erase the moved keys and children from the left (current) node
            node->keys.erase(node->keys.begin() + 1, node->keys.end());
            node->children.erase(node->children.begin() + 2, node->children.end());
            // Prepare result for parent
            res.hasPromoted = true;
            res.promotedKey = median;
            res.rightChild = right;
            return res;
        }
    }
    // No split at this level
    return res;
}

void insert23(Node23*& root, int key) {
    if (!root) {
        root = new Node23();
        root->keys.push_back(key);
        return;
    }
    InsertResult res = insertInternal(root, key);
    // If the root split, create a new root
    if (res.hasPromoted) {
        Node23* newRoot = new Node23();
        newRoot->keys.push_back(res.promotedKey);
        newRoot->children.push_back(root);
        newRoot->children.push_back(res.rightChild);
        root = newRoot;
    }
}

// Inorder traversal of 2–3 tree
void inorder23(Node23* node) {
    if (!node) return;
    if (node->keys.empty()) return;
    if (node->keys.size() == 1) {
        // left subtree
        if (!node->isLeaf()) inorder23(node->children[0]);
        std::cout << node->keys[0] << " ";
        if (!node->isLeaf()) inorder23(node->children[1]);
    } else { // size == 2
        if (!node->isLeaf()) inorder23(node->children[0]);
        std::cout << node->keys[0] << " ";
        if (!node->isLeaf()) inorder23(node->children[1]);
        std::cout << node->keys[1] << " ";
        if (!node->isLeaf()) inorder23(node->children[2]);
    }
}

// Recursively delete all nodes
void deleteTree23(Node23* node) {
    if (!node) return;
    for (Node23* child : node->children) {
        deleteTree23(child);
    }
    delete node;
}