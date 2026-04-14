#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include "AVL/avl.h"

using namespace std;

enum CollisionHandling {
    CHAINING_VECTOR,
    CHAINING_LIST,
    CHAINING_BST,
    LINEAR_PROBING,
    QUADRATIC_PROBING,
    DOUBLE_HASHING
};

class HashTable {
    private:
        int tableSize;
        int elementCount;
        CollisionHandling method;

        // Storage containers for the different variants
        vector<vector<pair<string, int>>> tableVector;
        vector<list<pair<string, int>>> tableList;
        vector<AVLTree> tableBST; // (uses AVLTree)
        vector<pair<string, int>> tableProbing;

        // Hash Functions and Collision Handling
        int hash1(const string& key) const;
        int hash2(const string& key) const;
        int probe(int index, int i) const;  // uses h2Cache for DOUBLE_HASHING
        void rehash();

        // Helper functions
        int findEmptySlot(const string& key);
        void resizeIfNeeded();

        // Caches hash2(key) before any probe sequence so probe() keeps its
        // original (index, i) signature while still supporting double hashing.
        mutable int h2Cache;

    public:
        HashTable(int size, CollisionHandling variant);
        ~HashTable();

        void insert(const string& key, int value); //COMPLETE THIS
        bool search(const string& key, int& value); // COMPLETE THIS
        bool remove(const string& key); // COMPLETE THIS

        // Benchmark and Display
        void benchmarkHashTable(HashTable& table, const vector<pair<string, int>>& data, int numSearch, int numDelete);
        void displayStats();
};

vector<pair<string, int>> readDataFromFile(const string& filename);
void benchmarkStdUnorderedMap(const vector<pair<string, int>>& data, int numSearch, int numDelete);

#endif
