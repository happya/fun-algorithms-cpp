#include <iostream>
#include "BST.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    auto bst = new BST<int>(3);
    bst->insertKey(4);
#include "BST.h"

using namespace std;
int main() {
    vector<int> a({6,4,7,2,8,5,9});
    auto bst = new BST<int>();
    for(auto n : a) {
        bst->insertKey(n);
    }
    bst->insertKey(1);
    bst->insertKey(3);
    bst->preOrder();
    bst->inOrder();
    auto node = bst->search(6);
    cout<<node->key<<endl;
    cout<<bst->preNode(node)->key<<endl;
    bst->removeKey(6);
    bst->inOrder();
    return 0;
}