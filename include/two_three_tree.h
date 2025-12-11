#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H

#include <vector>

/**
 * A minimal 2–3 tree implementation supporting insertion of integer keys
 * and an inorder traversal.  A 2–3 tree is a balanced search tree where
 * every internal node contains one or two keys and has two or three
 * children.  All leaves are at the same depth.  For educational
 * purposes this implementation only supports insertion and does not
 * handle deletion.
 */

struct Node23 {
    std::vector<int> keys;         ///< the keys stored in this node (size 1 or 2)
    std::vector<Node23*> children; ///< child pointers (size = keys.size()+1 or 0 for leaves)

    Node23() = default;

    /**
     * Return true if this node is a leaf.  A node is a leaf when it has
     * no children.
     */
    bool isLeaf() const { return children.empty(); }
};

/**
 * Insert a key into the 2–3 tree.  On return the root pointer may
 * change due to splits at the root.
 *
 * @param root reference to the root pointer of the tree
 * @param key  the key to insert
 */
void insert23(Node23*& root, int key);

/**
 * Perform an inorder traversal printing the keys to standard output.
 */
void inorder23(Node23* node);

/**
 * Recursively delete all nodes in the tree freeing memory.
 */
void deleteTree23(Node23* node);

#endif // TWO_THREE_TREE_H