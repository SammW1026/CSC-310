#include <iostream>
#include "LLRB.h"
#include "Includes/customErrorClass.h"

int main() {
    LLRBTree tree;

    try {

        tree.insert(10);
        tree.insert(16);
        tree.insert(5);
        tree.insert(15);
        tree.insert(6);
        tree.insert(8);

        std::cout << "In-order traversal: ";
        tree.printInOrder();

        std::cout << "\nTree structure ([R] = red, [B] = black):\n";
        tree.printTree();

        // duplicate insertion should throw
        tree.insert(10);

    } catch (MyException &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        std::cout << "\nContains 12: " << std::boolalpha << tree.contains(12) << std::endl;
        std::cout << "Contains 20: " << std::boolalpha << tree.contains(20) << std::endl;
    } catch (MyException &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}