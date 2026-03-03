#include "splay.h"

int main() {
    cout << "==== TOP-DOWN FULL SPLAY (CLASSIC APPROACH) ====" << endl;
    SplayTree treeTopDown;

    treeTopDown.insert(57);
    treeTopDown.insert(31);
    treeTopDown.insert(72);
    treeTopDown.insert(44);
    treeTopDown.insert(69);
    treeTopDown.insert(83);

    cout << "Tree after insertions: " << endl;
    treeTopDown.display();

    cout << "Searching for 44 (full splay)..." << endl;
    treeTopDown.search(44);
    cout << "Tree after splaying 44 to root: " << endl;
    treeTopDown.display();

    cout << "Removing 31 (top-down delete): " << endl;
    treeTopDown.remove(31);
    cout << "Tree after deleting 31: " << endl;
    treeTopDown.display();

    cout << "\n==== BOTTOM-UP SPLAY (BOTTOM-UP APPROACH) ====" << endl;
    SplayTree treeBottomUp;

    treeBottomUp.insert(57);
    treeBottomUp.insert(31);
    treeBottomUp.insert(72);
    treeBottomUp.insert(44);
    treeBottomUp.insert(69);
    treeBottomUp.insert(83);

    cout << "Tree after insertions: " << endl;
    treeBottomUp.display();

    cout << "Searching for 44 (bottom-up splay)..." << endl;
    treeBottomUp.searchBottomUp(44);
    cout << "Tree after splaying 44 to root: " << endl;
    treeBottomUp.display();

    cout << "Removing 31 (bottom-up delete): " << endl;
    treeBottomUp.removeBottomUp(31);
    cout << "Tree after deleting 31 and splaying parent: " << endl;
    treeBottomUp.display();

    cout << "\n==== SEMI-SPLAY WITH ROTATION LIMIT (REDUCES ROTATIONS) ====" << endl;
    SplayTree treeSemiSplay;

    treeSemiSplay.insert(57);
    treeSemiSplay.insert(31);
    treeSemiSplay.insert(72);
    treeSemiSplay.insert(44);
    treeSemiSplay.insert(69);
    treeSemiSplay.insert(83);

    cout << "Tree after insertions: " << endl;
    treeSemiSplay.display();

    cout << "Searching for 44 with rotation limit of 2..." << endl;
    treeSemiSplay.searchSemiSplay(44, 2);
    cout << "Tree after semi-splay (limited rotations): " << endl;
    treeSemiSplay.display();

    cout << "\n==== WEIGHTED-SPLAY WITH CACHE BEHAVIOR ====" << endl;
    SplayTree treeWeighted;

    treeWeighted.insert(57);
    treeWeighted.insert(31);
    treeWeighted.insert(72);
    treeWeighted.insert(44);
    treeWeighted.insert(69);
    treeWeighted.insert(83);

    cout << "Tree after insertions: " << endl;
    treeWeighted.display();

    cout << "First search for 44 (weighted splay - weight-based rotations)..." << endl;
    treeWeighted.searchWeightedSplay(44);
    cout << "Tree after weighted-splay (only rotates if child weight >= parent): " << endl;
    treeWeighted.display();

    cout << "Second search for 44 (weight now increased from first search)..." << endl;
    treeWeighted.searchWeightedSplay(44);
    cout << "Tree after second weighted-splay: " << endl;
    treeWeighted.display();

    cout << "\n==== COMPARISON SUMMARY ====" << endl;
    cout << "1. Full Splay: Moves target to root, best for frequently accessed nodes" << endl;
    cout << "2. Bottom-Up Splay: Same as full splay but traverses up from leaf" << endl;
    cout << "3. Semi-Splay: Limits rotations, balances cost vs. performance" << endl;
    cout << "4. Weighted-Splay: Cache-like behavior, rotates based on access frequency" << endl;

    return 0;
}
