#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// AVLTree class implements a self-balancing AVL tree, a type of binary search tree (BST)
// where the height difference between left and right subtrees is at most 1. This ensures
// O(log n) time for insert, delete, and search operations. The class includes functions to
// insert values, delete values, balance the tree, and print the tree using four traversal methods.
class AVLTree {
private:
    // Node structure represents a single node in the AVL tree
    struct Node {
        int value;          // The data value stored in the node
        Node* left;         // Pointer to the left child (values <= parent)
        Node* right;        // Pointer to the right child (values > parent)
        int height;         // Height of the node (used for balancing)
        // Constructor initializes a node with a value, null children, and height 1
        Node(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root; // Pointer to the root node of the tree (null if empty)

    // getHeight: Returns the height of a node. If the node is null, returns 0.
    // Used to calculate balance factors and update heights.
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // getBalance: Calculates the balance factor of a node (left height - right height).
    // A balance factor > 1 means left-heavy, < -1 means right-heavy, else balanced.
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // updateHeight: Updates the height of a node based on the maximum height of its children.
    // Height is 1 + max(left height, right height). Only called for non-null nodes.
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // rotateRight: Performs a right rotation on node y to fix a left-heavy imbalance.
    // Used in Left-Left or Left-Right cases. Returns the new root (x) of the rotated subtree.
    // Structure changes from:
    //       y              x
    //      /              / \
    //     x      to      T1  y
    //    / \                / \
    //   T1 T2              T2 T3
    Node* rotateRight(Node* y) {
        Node* x = y->left;          // x is the left child of y
        Node* T2 = x->right;        // T2 is the right subtree of x
        x->right = y;               // Make y the right child of x
        y->left = T2;               // Move T2 to y's left child
        updateHeight(y);            // Update y's height (now lower in the tree)
        updateHeight(x);            // Update x's height (now the root)
        return x;                   // Return new root of the subtree
    }

    // rotateLeft: Performs a left rotation on node x to fix a right-heavy imbalance.
    // Used in Right-Right or Right-Left cases. Returns the new root (y) of the rotated subtree.
    // Structure changes from:
    //       x              y
    //        \            / \
    //         y    to    x  T3
    //        / \        / \
    //       T2 T3      T1 T2
    Node* rotateLeft(Node* x) {
        Node* y = x->right;         // y is the right child of x
        Node* T2 = y->left;         // T2 is the left subtree of y
        y->left = x;                // Make x the left child of y
        x->right = T2;              // Move T2 to x's right child
        updateHeight(x);            // Update x's height (now lower)
        updateHeight(y);            // Update y's height (now the root)
        return y;                   // Return new root of the subtree
    }

    // insert: Recursively inserts a value into the BST. If the value exists, does nothing.
    // After insertion, updates heights and balances the tree to maintain AVL properties.
    // Returns the root of the modified subtree.
    Node* insert(Node* node, int value) {
        // If node is null, create a new node with the value
        if (!node) {
            return new Node(value);
        }
        // Insert into left subtree if value is less than node's value
        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        // Insert into right subtree if value is greater
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        // If value equals node's value, ignore (no duplicates)
        else {
            return node;
        }
        // Update the node's height after insertion
        updateHeight(node);
        // Balance the node to maintain AVL properties
        return balance(node);
    }

    // balance: Checks the balance factor of a node and performs rotations if needed.
    // Handles four cases: Left-Left, Left-Right, Right-Right, Right-Left.
    // Returns the root of the balanced subtree.
    Node* balance(Node* node) {
        int balanceFactor = getBalance(node);
        // Left Heavy (balance factor > 1)
        if (balanceFactor > 1) {
            // Left-Right case: left child's right subtree is heavy
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left); // Convert to Left-Left
            }
            return rotateRight(node); // Perform right rotation for Left-Left
        }
        // Right Heavy (balance factor < -1)
        if (balanceFactor < -1) {
            // Right-Left case: right child's left subtree is heavy
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right); // Convert to Right-Right
            }
            return rotateLeft(node); // Perform left rotation for Right-Right
        }
        // Node is balanced, no rotation needed
        return node;
    }

    // findMin: Finds the node with the minimum value in a subtree by traversing left.
    // Used in deletion when replacing a node with two children.
    // Returns the minimum node.
    Node* findMin(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // remove: Recursively deletes a value from the tree. Handles three cases:
    // 1. No child: Delete the node.
    // 2. One child: Replace node with its child.
    // 3. Two children: Replace with minimum of right subtree, then delete that minimum.
    // Updates heights and balances after deletion. Returns the root of the modified subtree.
    Node* remove(Node* node, int value) {
        // If node is null, value not found, return null
        if (!node) {
            return nullptr;
        }
        // Search left subtree if value is less than node's value
        if (value < node->value) {
            node->left = remove(node->left, value);
        }
        // Search right subtree if value is greater
        else if (value > node->value) {
            node->right = remove(node->right, value);
        }
        // Found the node to delete
        else {
            // Case 1: No left child, return right child (may be null)
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2: No right child, return left child
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children, replace with minimum of right subtree
            Node* minNode = findMin(node->right);
            node->value = minNode->value; // Copy minimum value
            node->right = remove(node->right, minNode->value); // Delete minimum
        }
        // Update height after deletion
        updateHeight(node);
        // Balance the node to maintain AVL properties
        return balance(node);
    }

    // preOrder: Recursively prints the tree in pre-order traversal (root, left, right).
    // Visits the current node first, then left subtree, then right subtree.
    void preOrder(Node* node) {
        if (node) {
            std::cout << node->value << " "; // Print current node's value
            preOrder(node->left);            // Traverse left subtree
            preOrder(node->right);           // Traverse right subtree
        }
    }

    // inOrder: Recursively prints the tree in in-order traversal (left, root, right).
    // Produces values in sorted order for a BST. Visits left subtree, current node, then right.
    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);             // Traverse left subtree
            std::cout << node->value << " "; // Print current node's value
            inOrder(node->right);            // Traverse right subtree
        }
    }

    // postOrder: Recursively prints the tree in post-order traversal (left, right, root).
    // Visits left subtree, right subtree, then current node.
    void postOrder(Node* node) {
        if (node) {
            postOrder(node->left);           // Traverse left subtree
            postOrder(node->right);          // Traverse right subtree
            std::cout << node->value << " "; // Print current node's value
        }
    }

    // levelOrder: Prints the tree in level-order traversal (breadth-first).
    // Uses a queue to visit nodes level by level, from left to right.
    void levelOrder(Node* node) {
        if (!node) return; // If tree is empty, do nothing
        std::queue<Node*> q; // Queue to store nodes for processing
        q.push(node);        // Start with the root
        while (!q.empty()) {
            Node* current = q.front(); // Get the front node
            q.pop();                   // Remove it from the queue
            std::cout << current->value << " "; // Print its value
            if (current->left) q.push(current->left);   // Add left child to queue
            if (current->right) q.push(current->right); // Add right child to queue
        }
    }

    // destroy: Recursively deletes all nodes in the tree to free memory.
    // Uses post-order traversal to delete children before the parent.
    void destroy(Node* node) {
        if (node) {
            destroy(node->left);  // Delete left subtree
            destroy(node->right); // Delete right subtree
            delete node;          // Delete current node
        }
    }

public:
    // Constructor, initializes an empty tree with null root
    AVLTree() : root(nullptr) {}

    // Destructor, deletes the entire tree to prevent memory leaks
    ~AVLTree() { destroy(root); }

    // Public insert, calls private recursive insert to add a value
    void insert(int value) {
        // root is a pointer to a node structure
        root = insert(root, value);
    }

    //public remove, calls private recursive remove to delete a value
    void remove(int value) {
        root = remove(root, value);
    }

    //public printPreOrder, prints the tree in pre-order traversal
    void printPreOrder() {
        std::cout << "Pre-order: ";
        preOrder(root);
        std::cout << std::endl;
    }

    //public printInOrder, prints the tree in in-order traversal (sorted)
    void printInOrder() {
        std::cout << "In-order: ";
        inOrder(root);
        std::cout << std::endl;
    }

    //public printPostOrder, prints the tree in post-order traversal
    void printPostOrder() {
        std::cout << "Post-order: ";
        postOrder(root);
        std::cout << std::endl;
    }

    //public printLevelOrder, prints the tree in level-order traversal
    void printLevelOrder() {
        std::cout << "Level-order: ";
        levelOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    // Creating the tree object
    AVLTree tree;
    srand(time(0));

    cout << "Inserting 10 random elements:\n";
    for (int i = 0; i < 10; i++) {
        int value = rand() % 100 + 1; // random value, 1-100
        cout << "Inserting " << value << endl;
        tree.insert(value);
    }

    // Print traversals
    std::cout << "\nAfter insertions:\n";
    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
    tree.printLevelOrder();

    // Delete 3 random values
    int deleteValues[] = {rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1};
    std::cout << "\nDeleting elements: ";
    for (int value : deleteValues) {
        std::cout << value << " ";
        tree.remove(value);
    }
    std::cout << "\n";

    // Print traversals after deletions
    std::cout << "\nAfter deletions:\n";
    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
    tree.printLevelOrder();

    return 0;
}
