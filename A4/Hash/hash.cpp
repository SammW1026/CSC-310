#include "hash.h"


HashTable::HashTable(int size, CollisionHandling variant)
{
    tableSize    = size;
    elementCount = 0;
    method       = variant;
    h2Cache      = 1;

    switch (method) {
        case CHAINING_VECTOR:   tableVector.resize(size);  break;
        case CHAINING_LIST:     tableList.resize(size);    break;
        case CHAINING_BST:      tableBST.resize(size);     break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:    tableProbing.resize(size); break;
    }
}

HashTable::~HashTable() {}

int HashTable::hash1(const string& key) const {
    unsigned long hash = 0;
    for (char c : key)
        hash = hash * 31 + c;
    return (int)(hash % tableSize);
}

int HashTable::hash2(const string& key) const {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;   // hash * 33 + c
    return (int)(1 + (hash % (tableSize - 1)));
}

int HashTable::probe(int index, int i) const {
    switch (method) {
        case LINEAR_PROBING:
            // (h1 + i) mod m
            return (index + i) % tableSize;

        case QUADRATIC_PROBING:
            // (h1 + i²) mod m  — long long prevents 32-bit overflow
            return (int)(((long long)index + (long long)i * i) % tableSize);

        case DOUBLE_HASHING:
            // (h1 + i·h2) mod m — h2Cache holds hash2(key) for the current key
            return (int)(((long long)index + (long long)i * h2Cache) % tableSize);

        default:
            return index;
    }
}

int HashTable::findEmptySlot(const string& key) {
    h2Cache = hash2(key);
    int index = hash1(key);
    for (int i = 0; i < tableSize; i++) {
        int slot = probe(index, i);
        if (tableProbing[slot].first.empty() ||
            tableProbing[slot].first == "__DELETED__")
            return slot;
    }
    return -1;
}

void HashTable::insert(const string& key, int value) {
    resizeIfNeeded();
    int index = hash1(key);

    switch (method) {
        // ── Chaining with vector ──────────────────────────────────────────
        case CHAINING_VECTOR:
            for (auto& p : tableVector[index]) {
                if (p.first == key) { p.second = value; return; } // update
            }
            tableVector[index].push_back({key, value});
            elementCount++;
            break;

        // ── Chaining with list ────────────────────────────────────────────
        case CHAINING_LIST:
            for (auto& p : tableList[index]) {
                if (p.first == key) { p.second = value; return; } // update
            }
            tableList[index].push_back({key, value});
            elementCount++;
            break;

        // ── Chaining with BST (AVL) ───────────────────────────────────────
        case CHAINING_BST: {
            int dummy;
            bool exists = tableBST[index].search(key, dummy);
            tableBST[index].insert(key, value); // AVL handles update internally
            if (!exists) elementCount++;
            break;
        }

        // ── Open addressing (linear / quadratic / double hashing) ─────────
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING: {
            h2Cache = hash2(key);   // cache once for the whole probe sequence
            int firstTombstone = -1;

            for (int i = 0; i < tableSize; i++) {
                int slot = probe(index, i);

                if (tableProbing[slot].first == key) {
                    tableProbing[slot].second = value; // key already present – update
                    return;
                } else if (tableProbing[slot].first == "__DELETED__") {
                    if (firstTombstone == -1) firstTombstone = slot; // remember first tombstone
                } else if (tableProbing[slot].first.empty()) {
                    // Prefer reusing a tombstone slot so we don't grow the
                    // probe chain length unnecessarily.
                    int target = (firstTombstone != -1) ? firstTombstone : slot;
                    tableProbing[target] = {key, value};
                    elementCount++;
                    return;
                }
            }
            // Every slot was visited; reuse the first tombstone if available.
            if (firstTombstone != -1) {
                tableProbing[firstTombstone] = {key, value};
                elementCount++;
            }
            break;
        }
    }
}

bool HashTable::search(const string& key, int& value) {
    int index = hash1(key);

    switch (method) {
        case CHAINING_VECTOR:
            for (auto& p : tableVector[index])
                if (p.first == key) { value = p.second; return true; }
            return false;

        case CHAINING_LIST:
            for (auto& p : tableList[index])
                if (p.first == key) { value = p.second; return true; }
            return false;

        case CHAINING_BST:
            return tableBST[index].search(key, value);

        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING: {
            h2Cache = hash2(key);
            for (int i = 0; i < tableSize; i++) {
                int slot = probe(index, i);

                if (tableProbing[slot].first == key) {
                    value = tableProbing[slot].second;
                    return true;
                }
                // A truly empty slot means the key was never inserted along
                // this probe sequence – stop early.
                if (tableProbing[slot].first.empty())
                    return false;
                // "__DELETED__" tombstones are skipped: the key might still
                // lie further along the sequence.
            }
            return false;
        }
    }
    return false;
}

bool HashTable::remove(const string& key) {
    int index = hash1(key);

    switch (method) {
        case CHAINING_VECTOR: {
            auto& bucket = tableVector[index];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->first == key) {
                    bucket.erase(it);
                    elementCount--;
                    return true;
                }
            }
            return false;
        }

        case CHAINING_LIST: {
            auto& bucket = tableList[index];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->first == key) {
                    bucket.erase(it);
                    elementCount--;
                    return true;
                }
            }
            return false;
        }

        case CHAINING_BST:
            if (tableBST[index].remove(key)) {
                elementCount--;
                return true;
            }
            return false;

        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING: {
            h2Cache = hash2(key);
            for (int i = 0; i < tableSize; i++) {
                int slot = probe(index, i);

                if (tableProbing[slot].first == key) {
                   tableProbing[slot] = {"__DELETED__", 0};
                    elementCount--;
                    return true;
                }
                if (tableProbing[slot].first.empty())
                    return false;
            }
            return false;
        }
    }
    return false;
}

void HashTable::rehash() {
    int newSize = tableSize * 2 + 1;    // odd size reduces clustering risk

    switch (method) {
        case CHAINING_VECTOR: {
            vector<pair<string, int>> all;
            for (auto& bucket : tableVector)
                for (auto& p : bucket) all.push_back(p);
            tableVector.clear();
            tableVector.resize(newSize);
            tableSize    = newSize;
            elementCount = 0;
            for (auto& p : all) insert(p.first, p.second);
            break;
        }
        case CHAINING_LIST: {
            vector<pair<string, int>> all;
            for (auto& bucket : tableList)
                for (auto& p : bucket) all.push_back(p);
            tableList.clear();
            tableList.resize(newSize);
            tableSize    = newSize;
            elementCount = 0;
            for (auto& p : all) insert(p.first, p.second);
            break;
        }
        case CHAINING_BST: {
            vector<pair<string, int>> all;
            for (auto& tree : tableBST) {
                auto elems = tree.inOrderTraversal();
                for (auto& p : elems) all.push_back(p);
            }
            tableBST.clear();
            tableBST.resize(newSize);
            tableSize    = newSize;
            elementCount = 0;
            for (auto& p : all) insert(p.first, p.second);
            break;
        }
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING: {
            vector<pair<string, int>> all;
            for (auto& entry : tableProbing)
                if (!entry.first.empty() && entry.first != "__DELETED__")
                    all.push_back(entry);
            tableProbing.clear();
            tableProbing.resize(newSize);
            tableSize    = newSize;
            elementCount = 0;
            for (auto& p : all) insert(p.first, p.second);
            break;
        }
    }
}

void HashTable::resizeIfNeeded() {
    double lf = (double)elementCount / tableSize;
    switch (method) {
        case CHAINING_VECTOR:
        case CHAINING_LIST:
        case CHAINING_BST:
            if (lf > 1.5) rehash();
            break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            if (lf > 0.7) rehash();
            break;
    }
}

vector<pair<string, int>> readDataFromFile(const string& filename) {
    vector<pair<string, int>> data;
    ifstream file(filename);
    if (!file) { cerr << "Error reading file: " << filename << endl; return data; }
    string key; int value;
    while (file >> key >> value)
        data.push_back({key, value});
    return data;
}

void HashTable::benchmarkHashTable(HashTable& table, const vector<pair<string, int>>& data,
                                   int numSearch, int numDelete) {
    auto start = chrono::high_resolution_clock::now();

    for (const auto& p : data)
        table.insert(p.first, p.second);

    auto insertEnd = chrono::high_resolution_clock::now();

    int value;
    for (int i = 0; i < numSearch; ++i)
        table.search(data[rand() % data.size()].first, value);

    auto searchEnd = chrono::high_resolution_clock::now();

    for (int i = 0; i < numDelete; ++i)
        table.remove(data[rand() % data.size()].first);

    auto end = chrono::high_resolution_clock::now();

    cout << "  Insert : " << chrono::duration_cast<chrono::microseconds>(insertEnd - start).count()     << " µs" << endl;
    cout << "  Search : " << chrono::duration_cast<chrono::microseconds>(searchEnd - insertEnd).count() << " µs" << endl;
    cout << "  Delete : " << chrono::duration_cast<chrono::microseconds>(end - searchEnd).count()       << " µs" << endl;
}

void HashTable::displayStats() {
    int total = 0, maxChain = 0, empty = 0;

    switch (method) {
        case CHAINING_VECTOR:
            for (auto& b : tableVector) {
                if (b.empty()) empty++;
                maxChain = max(maxChain, (int)b.size());
                total   += b.size();
            }
            break;
        case CHAINING_LIST:
            for (auto& b : tableList) {
                if (b.empty()) empty++;
                maxChain = max(maxChain, (int)b.size());
                total   += b.size();
            }
            break;
        case CHAINING_BST:
            for (auto& tree : tableBST) {
                auto elems = tree.inOrderTraversal();
                if (elems.empty()) empty++;
                else { maxChain = max(maxChain, (int)elems.size()); total += elems.size(); }
            }
            break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            for (auto& e : tableProbing) {
                if (!e.first.empty() && e.first != "__DELETED__") total++;
                else if (e.first.empty()) empty++;
            }
            break;
    }

    cout << "  Elements   : " << total << endl;
    cout << "  Load factor: " << (double)total / tableSize << endl;
    cout << "  Empty slots: " << empty << endl;
    if (method <= CHAINING_BST)
        cout << "  Max chain  : " << maxChain << endl;
}

void benchmarkStdUnorderedMap(const vector<pair<string, int>>& data,
                               int numSearch, int numDelete) {
    unordered_map<string, int> stdMap;
    auto start = chrono::high_resolution_clock::now();

    for (auto& p : data) stdMap[p.first] = p.second;
    auto insertEnd = chrono::high_resolution_clock::now();

    int value;
    for (int i = 0; i < numSearch; ++i) {
        auto it = stdMap.find(data[rand() % data.size()].first);
        if (it != stdMap.end()) value = it->second;
    }
    auto searchEnd = chrono::high_resolution_clock::now();

    for (int i = 0; i < numDelete; ++i)
        stdMap.erase(data[rand() % data.size()].first);

    auto end = chrono::high_resolution_clock::now();

    cout << "  Insert : " << chrono::duration_cast<chrono::microseconds>(insertEnd - start).count()     << " µs" << endl;
    cout << "  Search : " << chrono::duration_cast<chrono::microseconds>(searchEnd - insertEnd).count() << " µs" << endl;
    cout << "  Delete : " << chrono::duration_cast<chrono::microseconds>(end - searchEnd).count()       << " µs" << endl;
}
