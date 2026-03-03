#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
using namespace std;

class SplayTree {
    private:
        struct Node {
            int key;
            Node* left;
            Node* right;
            int weight; // access frequency for weighted-splay
            Node(int k) {
                key = k;
                left = nullptr;
                right = nullptr; 
                weight = 0;
            }
        };

        Node* root;

        // rotation counter for benchmarking
        long long rotationCount = 0;

        Node* rotateRight(Node* x);
        Node* rotateLeft(Node* x);
        Node* splay(Node* root, int key);
        Node* splayBottomUp(Node* root, int key);
        Node* insertNode(Node* root, int key);
        Node* deleteNode(Node* root, int key);
        Node* deleteNodeBottomUp(Node* root, int key);

        // variants (stubs/optional): semi-splay (limit) and weighted-splay
        Node* splayWithLimit(Node* root, int key, int limit);
        Node* weightedSplay(Node* root, int key);

        void printTree(Node* root, int space);

    public:
        SplayTree();
        void insert(int key);
        void remove(int key);
        void removeBottomUp(int key);
        bool search(int key);
        bool searchBottomUp(int key);
        bool searchSemiSplay(int key, int rotationLimit);
        bool searchWeightedSplay(int key);
        void display();
};

#endif 
