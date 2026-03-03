#include "splay.h"
#include "Includes/customErrorClass.h"
#include <vector>

SplayTree::SplayTree() 
{
    root = nullptr; 
}

// aka Zig
SplayTree::Node* SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// aka Zag
SplayTree::Node* SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Bottom-up splay: Find the node, store path, then splay up
SplayTree::Node* SplayTree::splayBottomUp(Node* root, int key) {
    if (root == nullptr) return nullptr;

    // Find the node and store path
    vector<Node*> path;
    Node* current = root;
    
    while (current != nullptr) {
        path.push_back(current);
        if (key == current->key) {
            break;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        return root; // Key not found, return unchanged tree
    }

    // Now splay up along the path
    while (path.size() > 1) {
        Node* child = path.back();
        path.pop_back();
        Node* parent = path.back();

        if (path.size() == 1) {
            // Zig: child is direct child of root
            if (parent->left == child) {
                parent = rotateRight(parent);
            } else {
                parent = rotateLeft(parent);
            }
            rotationCount++;
            root = parent;
        } else {
            path.pop_back();
            Node* grandparent = path.back();
            path.push_back(parent); // restore parent for next iteration

            if (grandparent->left == parent) {
                if (parent->left == child) {
                    // Zig-zig (left-left)
                    grandparent = rotateRight(grandparent);
                    parent = grandparent->right;
                    parent = rotateRight(parent);
                    grandparent->right = parent;
                } else {
                    // Zig-zag (left-right)
                    parent = rotateLeft(parent);
                    grandparent->left = parent;
                    grandparent = rotateRight(grandparent);
                }
            } else {
                if (parent->right == child) {
                    // Zig-zig (right-right)
                    grandparent = rotateLeft(grandparent);
                    parent = grandparent->left;
                    parent = rotateLeft(parent);
                    grandparent->left = parent;
                } else {
                    // Zig-zag (right-left)
                    parent = rotateRight(parent);
                    grandparent->right = parent;
                    grandparent = rotateLeft(grandparent);
                }
            }
            rotationCount += 2;
            root = grandparent;
        }
    }

    return root;
}

// Splaying :) (Top-down approach)
SplayTree::Node* SplayTree::splay(Node* root, int key) {
    if (root == nullptr) return nullptr;

    // Top-down splay
    Node header(0); // temporary tree
    Node* leftTreeMax = &header;
    Node* rightTreeMin = &header;

    Node* t = root;
    while (true) {
        if (key < t->key) {
            if (t->left == nullptr) break;
            if (key < t->left->key) {
                // rotate right
                t = rotateRight(t);
                rotationCount++;
                if (t->left == nullptr) break;
            }
            // link to right tree
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        } else if (key > t->key) {
            if (t->right == nullptr) break;
            if (key > t->right->key) {
                // rotate left
                t = rotateLeft(t);
                rotationCount++;
                if (t->right == nullptr) break;
            }
            // link to left tree
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        } else {
            break;
        }
    }

    // assemble
    rightTreeMin->left = t->right;
    leftTreeMax->right = t->left;
    t->left = header.right;
    t->right = header.left;

    return t;
}


SplayTree::Node* SplayTree::insertNode(Node* root, int key) {
    if (root == nullptr) {
        Node* n = new Node(key);
        return n;
    }

    root = splay(root, key);

    if (root->key == key) {
        return root; // duplicate, do nothing
    }

    Node* n = new Node(key);
    if (key < root->key) {
        n->right = root;
        n->left = root->left;
        root->left = nullptr;
        root = n;
    } else {
        n->left = root;
        n->right = root->right;
        root->right = nullptr;
        root = n;
    }

    return root;
}


SplayTree::Node* SplayTree::deleteNode(Node* root, int key) {
    if (root == nullptr) {
        throw MyException("Delete from empty tree");
    }

    root = splay(root, key);

    if (root->key != key) {
        throw MyException("Key not found");
    }

    Node* temp;
    if (root->left == nullptr) {
        temp = root->right;
    } else {
        // splay the maximum node in left subtree
        Node* leftSub = root->left;
        // find max key in leftSub
        Node* maxNode = leftSub;
        while (maxNode->right != nullptr) maxNode = maxNode->right;
        leftSub = splay(leftSub, maxNode->key);
        // now leftSub is root of left subtree and max node is root
        leftSub->right = root->right;
        temp = leftSub;
    }

    delete root;
    return temp;
}


void SplayTree::insert(int key) {
    root = insertNode(root, key);
}


void SplayTree::remove(int key) {
    root = deleteNode(root, key);
}


bool SplayTree::search(int key) {
    root = splay(root, key);
    if (root && root->key == key) {
        root->weight++;
        return true;
    }
    return false;
}


bool SplayTree::searchBottomUp(int key) {
    root = splayBottomUp(root, key);
    if (root && root->key == key) {
        root->weight++;
        return true;
    }
    return false;
}


bool SplayTree::searchSemiSplay(int key, int rotationLimit) {
    root = splayWithLimit(root, key, rotationLimit);
    if (root && root->key == key) {
        root->weight++;
        return true;
    }
    return false;
}


bool SplayTree::searchWeightedSplay(int key) {
    root = weightedSplay(root, key);
    if (root && root->key == key) {
        root->weight++;
        return true;
    }
    return false;
}


void SplayTree::removeBottomUp(int key) {
    root = deleteNodeBottomUp(root, key);
}


SplayTree::Node* SplayTree::deleteNodeBottomUp(Node* root, int key) {
    if (root == nullptr) {
        throw MyException("Delete from empty tree");
    }

    // Find the node and store path
    vector<Node*> path;
    Node* current = root;
    
    while (current != nullptr) {
        path.push_back(current);
        if (key == current->key) {
            break;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        throw MyException("Key not found");
    }

    // Delete the node
    Node* temp;
    if (current->left == nullptr) {
        temp = current->right;
    } else {
        Node* maxInLeft = current->left;
        while (maxInLeft->right != nullptr) {
            maxInLeft = maxInLeft->right;
        }
        // Find max via bottom-up splay
        Node* leftSub = current->left;
        leftSub = splayBottomUp(leftSub, maxInLeft->key);
        leftSub->right = current->right;
        temp = leftSub;
    }

    delete current;

    // Now splay the parent of deleted node
    if (path.size() > 1) {
        path.pop_back(); // Remove the deleted node
        Node* parent = path.back();
        // Splay the parent
        root = splayBottomUp(root, parent->key);
    } else {
        root = temp;
    }

    return root;
}


SplayTree::Node* SplayTree::splayWithLimit(Node* root, int key, int limit) {
    if (root == nullptr) return nullptr;

    Node header(0);
    Node* leftTreeMax = &header;
    Node* rightTreeMin = &header;

    Node* t = root;
    int rotations = 0;
    while (true) {
        // Stop if rotation limit reached
        if (limit >= 0 && rotations >= limit) break;
        
        if (key < t->key) {
            if (t->left == nullptr) break;
            // Perform zig or zig-zig based on available rotations
            if (key < t->left->key && (limit < 0 || rotations + 1 < limit)) {
                // Zig-zig: we have room for 2 rotations
                t = rotateRight(t);
                rotationCount++;
                rotations++;
                if (t->left == nullptr) break;
            }
            // Single zig
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        } else if (key > t->key) {
            if (t->right == nullptr) break;
            // Perform zag or zag-zag based on available rotations
            if (key > t->right->key && (limit < 0 || rotations + 1 < limit)) {
                // Zag-zag: we have room for 2 rotations
                t = rotateLeft(t);
                rotationCount++;
                rotations++;
                if (t->right == nullptr) break;
            }
            // Single zag
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        } else {
            break;
        }
    }

    // assemble the tree
    rightTreeMin->left = t->right;
    leftTreeMax->right = t->left;
    t->left = header.right;
    t->right = header.left;
    return t;
}


SplayTree::Node* SplayTree::weightedSplay(Node* root, int key) {
    if (root == nullptr) return nullptr;

    Node header(0);
    Node* leftTreeMax = &header;
    Node* rightTreeMin = &header;

    Node* t = root;
    while (true) {
        if (key < t->key) {
            if (t->left == nullptr) break;
            if (t->left->weight >= t->weight && key < t->left->key) {
                t = rotateRight(t);
                rotationCount++;
                if (t->left == nullptr) break;
            }
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        } else if (key > t->key) {
            if (t->right == nullptr) break;
            if (t->right->weight >= t->weight && key > t->right->key) {
                t = rotateLeft(t);
                rotationCount++;
                if (t->right == nullptr) break;
            }
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        } else break;
    }

    rightTreeMin->left = t->right;
    leftTreeMax->right = t->left;
    t->left = header.right;
    t->right = header.left;
    return t;
}


void SplayTree::printTree(Node* root, int space) {
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
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}

void SplayTree::display() {
    printTree(root, 0);
    cout << endl;
}
