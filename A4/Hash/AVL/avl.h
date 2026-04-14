#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    pair<string, int> data; // Store key-value pair
    Node* left;
    Node* right;
    int height;

    Node(const pair<string, int>& val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const string& key, int value);
    bool remove(const string& key);
    bool search(const string& key, int& value);
    void print();

    void inOrderTraversal(Node* node, vector<pair<string, int>>& result) const;
    vector<pair<string, int>> inOrderTraversal() const;

private:
    Node* root;

    Node* insert(Node* node, const pair<string, int>& data);
    Node* remove(Node* node, const string& key);
    Node* minValueNode(Node* node);

    int height(Node* node);
    int getBalanceFactor(Node* node);

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    Node* search(Node* node, const string& key, int& value);
    void printTree(Node* root, int space);
    void destroyTree(Node* node);
};

#endif