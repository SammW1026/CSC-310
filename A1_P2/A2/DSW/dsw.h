#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <math.h>
#include "Includes/customErrorClass.h"

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST 
{
    private:
        Node* root;

        // Helper functions
        void rotateRight(Node*& node);
        void rotateLeft(Node*& node);
        int getSize(Node* node);  // Get size of subtree
        void createVine();  // Phase 1
        void rebuildTree(int size);  // Phase 2
        void performRotation(int count);  // helper for phase 2 (rebuildTree)
        void printTree(Node* root, int space);

    public:
        BST();
        ~BST();
        // helper for the destructor
        void deleteTree(Node*& node);

        void insert(int val);
        void dswBalance();

        void display();

};

#endif