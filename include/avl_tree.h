#ifndef AVL_TREE_H
#define AVL_TREE_H

/**
 * A simple implementation of an AVL tree for integer keys.
 *
 * AVL trees are self‑balancing binary search trees.  After each insertion
 * the tree rebalances itself by performing rotations when necessary.  For
 * educational purposes this implementation exposes basic operations such
 * as insertion, rotation and an inorder traversal.  Memory management is
 * manual – remember to call deleteTree when finished using the tree.
 */

struct AVLNode {
    int key;          ///< key stored in this node
    int height;       ///< height of the subtree rooted at this node
    AVLNode* left;    ///< pointer to the left child
    AVLNode* right;   ///< pointer to the right child

    /**
     * Construct a new AVLNode storing the given key.  The node is
     * initialised as a leaf with height 1 and no children.
     */
    explicit AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

/**
 * Return the height of the given node.  A null pointer is treated as
 * having height zero.
 */
int height(AVLNode* node);

/**
 * Compute the balance factor of a node.  The balance factor is the
 * difference between the heights of the left and right subtrees.
 */
int getBalance(AVLNode* node);

/**
 * Perform a right rotation on the given subtree rooted at y and
 * return the new root of the rotated subtree.
 */
AVLNode* rotateRight(AVLNode* y);

/**
 * Perform a left rotation on the given subtree rooted at x and
 * return the new root of the rotated subtree.
 */
AVLNode* rotateLeft(AVLNode* x);

/**
 * Insert a key into the AVL tree rooted at the given node.  The tree
 * remains balanced after insertion.  The function returns the (possibly
 * new) root of the subtree after insertion.
 */
AVLNode* avlInsert(AVLNode* node, int key);

/**
 * Perform an inorder traversal of the AVL tree printing the keys to
 * standard output.  Keys are separated by spaces.
 */
void inorder(AVLNode* root);

/**
 * Recursively delete all nodes in the AVL tree freeing memory.  After
 * calling this function the given pointer should not be used again.
 */
void deleteTree(AVLNode* root);

#endif // AVL_TREE_H