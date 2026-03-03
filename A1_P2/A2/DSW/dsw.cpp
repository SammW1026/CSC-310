#include "dsw.h"

// ----------------- PRIVATE ----------------------------------

// when left-heavy tree
void BST::rotateRight(Node*& node) // passing the parent
{
    if(node == nullptr || node->left == nullptr)
        return;
    
    // get the node to rotate R
    Node* leftChild = node->left; 
    // 1) leftnode's right child is going to become parent's left child
    node->left = leftChild->right;
    // 2) parent is going to be right child of node that is rotated
    leftChild->right = node;
    
    node = leftChild;
}

// when right-heavy
void BST::rotateLeft(Node*& node)
{
    if(node == nullptr || node->right == nullptr)
        return;

    // get the node to rotate L
    Node* rightChild = node->right;
    // 1) rightnode's left child is going to become parent's right child
    node->right = rightChild->left;
    // 2) parent is going to be left child of node that is rotated
    rightChild->left = node;

    node = rightChild;
}

// Helper function to get the size of a subtree
int BST::getSize(Node* node)
{
    if (node == nullptr) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}

// Phase 1 - Create a partially left skewed vine
// Rotate left if right subtree is large (size > 2), skip small subtrees
void BST::createVine()
{
    try {
        if (root == nullptr) {
            throw MyException("Cannot create vine from empty tree!");
        }
        
        Node* curr = root;
        
        while (curr != nullptr) {
            // Keep rotating left while right child exists and subtree is large (> 2 nodes)
            while (curr->right != nullptr && getSize(curr->right) > 2) {
                rotateLeft(curr);
            }
            // Move to the right child (skip small right subtrees with size <= 2)
            curr = curr->right;
        }
    } catch (MyException &e) {
        cerr << "Error in createVine: " << e.what() << endl;
        throw;
    }
}

void BST::rebuildTree(int size)
{
    try {
        if (size <= 1) return;
        
        if (size < 0) {
            throw MyException("Invalid tree size for rebuild!");
        }
        
        int n = size;
        // Calculate the size of the largest perfect binary tree that fits
        // m = 2^floor(log2(n+1)) - 1
        int m = (1 << (int)log2(n + 1)) - 1;
        
        // Validate calculated parameters
        if (m > n) {
            throw MyException("Invalid calculation in rebuildTree!");
        }
        
        // Phase 2a: Do initial rotations to handle excess nodes
        performRotation(n - m);
        
        // Phase 2b: Recursively balance the remaining structure
        // Keep height close to 2*log2(N) by continuing rotations
        for (n = m / 2; n > 0; n /= 2) {
            performRotation(n);
        }
    } catch (MyException &e) {
        cerr << "Error in rebuildTree: " << e.what() << endl;
        throw;
    }
}

// Right rotate every second node along right spine
void BST::performRotation(int count)
{
    Node* curr = root;
    
    for (int i = 0; i < count; i++) {
        if (curr == nullptr) break;
        
        // Rotate right at current node (brings left child up as new root)
        rotateRight(curr);
        
        // Move down right spine: skip one node, then rotate the next
        // First move to right child
        if (curr->right != nullptr) {
            curr = curr->right;
        } else {
            break;
        }
        
        // Second move to skip one node
        if (curr->right != nullptr) {
            curr = curr->right;
        } else {
            break;
        }
    }
}

void BST::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->data << endl;

    // Print the left child
    printTree(root->left, space);
}

// --------------------- PUBLIC ------------------
BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    deleteTree(root);
}

void BST::deleteTree(Node*& node)
{
    if(node == nullptr)
        return;
    
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void BST::insert(int val)
{
    try {
        Node* newNode = new Node(val);
        if(root == nullptr){
            root = newNode;
            return;
        }
        
        Node* curr = root;
        Node* parent = nullptr;

        while(curr != nullptr)
        {
            parent = curr;
            if(val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if(val < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    } catch (bad_alloc &e) {
        throw MyException("Memory allocation failed during insert!");
    }
}

void BST::dswBalance()
{
    try {
        // Check if tree is empty
        if (root == nullptr) {
            throw MyException("Cannot balance an empty tree!");
        }

        // Get the total number of nodes
        int size = getSize(root);
        
        // Check if tree has only one node (already balanced)
        if (size <= 1) {
            cout << "Tree has only one node - already balanced!" << endl;
            return;
        }
        
        // Phase 1: Create a partially left-skewed vine
        // Skip rotations for small right subtrees (size <= 2)
        createVine();
        
        // Phase 2: Rebalance the vine structure
        // Keep height close to 2*log2(N)
        rebuildTree(size);
    } catch (MyException &e) {
        cerr << "Error during DSW balancing: " << e.what() << endl;
        throw;
    }
}

void BST::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}