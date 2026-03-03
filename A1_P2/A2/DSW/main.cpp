#include "dsw.h"

int main()
{
    BST bst;

    try {
        // bst.insert(10);
        // bst.insert(14);
        // bst.insert(23);
        // bst.insert(8);
        // bst.insert(7);
        // bst.insert(9);
        // bst.insert(20);
        // bst.insert(25);
        bst.insert(2);
        bst.insert(3);
        bst.insert(19);
        bst.insert(27);
        bst.insert(20);
        bst.insert(36);
        bst.insert(30);
        bst.insert(59);
        bst.insert(43);
        bst.insert(40);
        cout << "Orginal BST:";
        bst.display();

        bst.dswBalance();

        cout << "DSW balanced BST:";
        bst.display();
    } catch (MyException &e) {
        cerr << "Exception caught in main: " << e.what() << endl;
        return 1;
    }

    return 0;
}