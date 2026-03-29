#ifndef LLRB_H
#define LLRB_H

#include "Includes/customErrorClass.h"

class LLRBTree {
public:
    LLRBTree();
    ~LLRBTree();

    void insert(int key);
    bool contains(int key) const;
    void printInOrder() const;
    void printTree() const;

private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        bool red;

        Node(int k, bool c): key(k), left(nullptr), right(nullptr), red(c) {}
    };

    Node* root;

    static bool isRed(Node* x) { return x != nullptr && x->red; }

    Node* rotateLeft(Node* h);
    Node* rotateRight(Node* h);
    void flipColors(Node* h);
    Node* insertNode(Node* h, int key);
    Node* fixUp(Node* h);
    bool containsNode(Node* h, int key) const;
    void inorder(Node* h) const;
    void deleteTree(Node* h);
    void printTreeHelper(Node* h, const string& prefix, bool isLeft) const;
};

#endif // LLRB_H