#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <iostream>
#include <climits>
#include "customErrorClass.h"

struct BinomialNode {
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int k)
        : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    BinomialNode* head;

    void linkTrees(BinomialNode* y, BinomialNode* z);
    BinomialNode* mergeRoots(BinomialNode* h1, BinomialNode* h2);
    BinomialNode* unionHeaps(BinomialNode* h1, BinomialNode* h2);
    BinomialNode* findNode(BinomialNode* node, int key);
    void bubbleUp(BinomialNode* node);
    void deleteTree(BinomialNode* node);
    void displayTree(BinomialNode* node, int indent);

public:
    BinomialHeap();
    ~BinomialHeap();

    void insert(int key);
    int minimum();
    void deleteMin();
    void decreaseKey(int oldKey, int newKey);
    void deleteKey(int key);
    bool isEmpty();
    void display();
};

#endif
