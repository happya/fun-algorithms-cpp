#include <iostream>
#include "MagicTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto bst = new BST<int>(3);
    bst->insertKey(4);
    return 0;
}