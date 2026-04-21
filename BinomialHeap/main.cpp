#include <iostream>
#include "BinomialHeap.h"
#include "customErrorClass.h"

using namespace std;

static void printMin(BinomialHeap& h) {
    try {
        cout << "  Minimum: " << h.minimum() << "\n";
    } catch (MyException &e) {
        cerr << "  [MyException] " << e.what() << "\n";
    }
}

int main() {
    BinomialHeap heap;

    cout << "=== Insert 10, 20, 5, 15, 30 ===\n";
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(30);
    heap.display();
    printMin(heap);

    cout << "\n=== deleteMin() ===\n";
    heap.deleteMin();
    heap.display();
    printMin(heap);

    cout << "\n=== decreaseKey(20 -> 3) ===\n";
    heap.decreaseKey(20, 3);
    heap.display();
    printMin(heap);

    cout << "\n=== deleteKey(15) ===\n";
    heap.deleteKey(15);
    heap.display();
    printMin(heap);

    // ── Exception handling ──────────────────────────────────────────────────

    cout << "\n=== Exception: decreaseKey with newKey > oldKey ===\n";
    try {
        heap.decreaseKey(10, 99);
    } catch (MyException &e) {
        cerr << "  [MyException] " << e.what() << "\n";
    }

    cout << "\n=== Exception: decreaseKey on missing key ===\n";
    try {
        heap.decreaseKey(999, 1);
    } catch (MyException &e) {
        cerr << "  [MyException] " << e.what() << "\n";
    }

    cout << "\n=== Exception: deleteKey on missing key ===\n";
    try {
        heap.deleteKey(999);
    } catch (MyException &e) {
        cerr << "  [MyException] " << e.what() << "\n";
    }

    cout << "\n=== Drain remaining elements with deleteMin() ===\n";
    while (!heap.isEmpty()) {
        cout << "  Removed min: " << heap.minimum() << "\n";
        heap.deleteMin();
    }

    cout << "\n=== Exception: deleteMin on empty heap ===\n";
    try {
        heap.deleteMin();
    } catch (MyException &e) {
        cerr << "  [MyException] " << e.what() << "\n";
    }

    cout << "\n=== Exception: minimum on empty heap ===\n";
    printMin(heap);

    return 0;
}
