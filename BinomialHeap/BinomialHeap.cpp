#include "BinomialHeap.h"

// Make y a child of z; y and z must have the same degree
void BinomialHeap::linkTrees(BinomialNode* y, BinomialNode* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Merge two root lists into one sorted by degree (does not consolidate)
BinomialNode* BinomialHeap::mergeRoots(BinomialNode* h1, BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    BinomialNode* mergedHead = nullptr;
    BinomialNode* tail = nullptr;

    while (h1 && h2) {
        BinomialNode* next;
        if (h1->degree <= h2->degree) {
            next = h1;
            h1 = h1->sibling;
        } else {
            next = h2;
            h2 = h2->sibling;
        }
        next->sibling = nullptr;
        if (!mergedHead) {
            mergedHead = tail = next;
        } else {
            tail->sibling = next;
            tail = next;
        }
    }

    if (h1) tail->sibling = h1;
    if (h2) tail->sibling = h2;

    return mergedHead;
}

// Merge two heaps and consolidate trees of the same degree
BinomialNode* BinomialHeap::unionHeaps(BinomialNode* h1, BinomialNode* h2) {
    BinomialNode* newHead = mergeRoots(h1, h2);
    if (!newHead) return nullptr;

    BinomialNode* prev = nullptr;
    BinomialNode* curr = newHead;
    BinomialNode* next = curr->sibling;

    while (next) {
        // Case 1: degrees differ, or three consecutive roots share a degree
        if (curr->degree != next->degree ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else if (curr->key <= next->key) {
            // Case 2: curr wins — link next under curr
            curr->sibling = next->sibling;
            linkTrees(next, curr);
        } else {
            // Case 3: next wins — link curr under next
            if (!prev) {
                newHead = next;
            } else {
                prev->sibling = next;
            }
            linkTrees(curr, next);
            curr = next;
        }
        next = curr->sibling;
    }

    return newHead;
}

// Recursive search through children and siblings
BinomialNode* BinomialHeap::findNode(BinomialNode* node, int key) {
    if (!node) return nullptr;
    if (node->key == key) return node;

    BinomialNode* result = findNode(node->child, key);
    if (result) return result;

    return findNode(node->sibling, key);
}

// Swap key upward until heap-order is restored
void BinomialHeap::bubbleUp(BinomialNode* node) {
    while (node->parent && node->key < node->parent->key) {
        std::swap(node->key, node->parent->key);
        node = node->parent;
    }
}

void BinomialHeap::deleteTree(BinomialNode* node) {
    if (!node) return;
    deleteTree(node->child);
    deleteTree(node->sibling);
    delete node;
}

void BinomialHeap::displayTree(BinomialNode* node, int indent) {
    if (!node) return;
    std::cout << std::string(indent * 2, ' ') << node->key
              << " (deg=" << node->degree << ")\n";
    displayTree(node->child, indent + 1);
    displayTree(node->sibling, indent);
}

// ── Public interface ────────────────────────────────────────────────────────

BinomialHeap::BinomialHeap() : head(nullptr) {}

BinomialHeap::~BinomialHeap() {
    deleteTree(head);
}

void BinomialHeap::insert(int key) {
    BinomialNode* node = new BinomialNode(key);
    head = unionHeaps(head, node);
}

int BinomialHeap::minimum() {
    if (!head) throw MyException("Heap is empty");

    int minKey = head->key;
    BinomialNode* curr = head->sibling;
    while (curr) {
        if (curr->key < minKey) minKey = curr->key;
        curr = curr->sibling;
    }
    return minKey;
}

// Task 1: Remove the node with the minimum key
void BinomialHeap::deleteMin() {
    if (!head) throw MyException("Heap is empty — cannot deleteMin");

    // Find the root with the minimum key
    BinomialNode* minPrev = nullptr;
    BinomialNode* minNode = head;
    BinomialNode* prev = nullptr;
    BinomialNode* curr = head;

    while (curr) {
        if (curr->key < minNode->key) {
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    // Detach minNode from the root list
    if (minPrev) {
        minPrev->sibling = minNode->sibling;
    } else {
        head = minNode->sibling;
    }

    // Reverse minNode's child list and clear parent pointers
    BinomialNode* childHead = nullptr;
    BinomialNode* child = minNode->child;
    while (child) {
        BinomialNode* nextChild = child->sibling;
        child->sibling = childHead;
        child->parent = nullptr;
        childHead = child;
        child = nextChild;
    }

    // Merge remaining heap with the reversed children
    head = unionHeaps(head, childHead);

    delete minNode;
}

// Task 2: Decrease the key of a node identified by its current value
void BinomialHeap::decreaseKey(int oldKey, int newKey) {
    if (newKey > oldKey)
        throw MyException("New key (" + to_string(newKey) +
                          ") must be <= old key (" + to_string(oldKey) + ")");

    BinomialNode* node = findNode(head, oldKey);
    if (!node)
        throw MyException("Key " + to_string(oldKey) + " not found in heap");

    node->key = newKey;
    bubbleUp(node);
}

// Task 3: Delete the node identified by key
void BinomialHeap::deleteKey(int key) {
    if (!head) throw MyException("Heap is empty — cannot deleteKey");

    BinomialNode* node = findNode(head, key);
    if (!node)
        throw MyException("Key " + to_string(key) + " not found in heap");

    // Decrease to INT_MIN so it bubbles to the top, then extract
    node->key = INT_MIN;
    bubbleUp(node);
    deleteMin();
}

bool BinomialHeap::isEmpty() {
    return head == nullptr;
}

void BinomialHeap::display() {
    if (!head) {
        std::cout << "(empty heap)\n";
        return;
    }
    BinomialNode* curr = head;
    while (curr) {
        std::cout << "B" << curr->degree << " tree (root=" << curr->key << "):\n";
        displayTree(curr->child, 1);
        curr = curr->sibling;
    }
}
