#include <iostream>
<<<<<<< HEAD
#include "MagicTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto bst = new BST<int>(3);
    bst->insertKey(4);
=======
#include "BST.h"

using namespace std;
int main() {
    auto bst = new BST<int>();
    bst->insertKey(1);
    bst->insertKey(3);
    bst->preOrder();
>>>>>>> fd7ef94... finish BST.
    return 0;
}