#include "LLRB.h"
#include <iostream>
#include <limits>

using namespace std;

LLRBTree::LLRBTree() : root(nullptr) {}

LLRBTree::~LLRBTree() {
    deleteTree(root);
}

void LLRBTree::deleteTree(Node* h) {
    if (!h) return;
    deleteTree(h->left);
    deleteTree(h->right);
    delete h;
}

LLRBTree::Node* LLRBTree::rotateLeft(Node* h) {
    if (!h || !h->right) return h;
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->red = h->red;
    h->red = true;
    return x;
}

LLRBTree::Node* LLRBTree::rotateRight(Node* h) {
    if (!h || !h->left) return h;
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->red = h->red;
    h->red = true;
    return x;
}

void LLRBTree::flipColors(Node* h) {
    if (!h || !h->left || !h->right) {
        throw MyException("Color flip requires full node with two children");
    }
    h->red = !h->red;
    h->left->red = !h->left->red;
    h->right->red = !h->right->red;
}

LLRBTree::Node* LLRBTree::fixUp(Node* h) {
    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right)) flipColors(h);
    return h;
}

LLRBTree::Node* LLRBTree::insertNode(Node* h, int key) {
    if (!h) {
        return new Node(key, true);
    }

    if (key == h->key) {
        throw MyException("Duplicate key insertion is not allowed");
    } else if (key < h->key) {
        h->left = insertNode(h->left, key);
    } else {
        h->right = insertNode(h->right, key);
    }

    return fixUp(h);
}

void LLRBTree::insert(int key) {
    if (key == numeric_limits<int>::min()) {
        throw MyException("Invalid key value for insertion");
    }

    root = insertNode(root, key);
    if (root) root->red = false;
}

bool LLRBTree::containsNode(Node* h, int key) const {
    while (h) {
        if (key == h->key) return true;
        h = (key < h->key) ? h->left : h->right;
    }
    return false;
}

bool LLRBTree::contains(int key) const {
    if (!root) {
        throw MyException("Search in empty tree");
    }
    return containsNode(root, key);
}

void LLRBTree::inorder(Node* h) const {
    if (!h) return;
    inorder(h->left);
    cout << h->key << " ";
    inorder(h->right);
}

void LLRBTree::printInOrder() const {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    inorder(root);
    cout << '\n';
}

void LLRBTree::printTreeHelper(Node* h, const string& prefix, bool isLeft) const {
    if (!h) return;

    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");

    string color = h->red ? "[R]" : "[B]";
    cout << color << " " << h->key << "\n";

    string childPrefix = prefix + (isLeft ? "│   " : "    ");
    printTreeHelper(h->left,  childPrefix, true);
    printTreeHelper(h->right, childPrefix, false);
}

void LLRBTree::printTree() const {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    cout << "[B] " << root->key << "\n";
    printTreeHelper(root->left,  "", true);
    printTreeHelper(root->right, "", false);
}