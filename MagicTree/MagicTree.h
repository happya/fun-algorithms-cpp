//
// Created by yyi on 10/11/19.
//

#ifndef GRAPHBASIC_MAGICTREE_H
#define GRAPHBASIC_MAGICTREE_H

using namespace std;

template <typename Item>
class TreeNode {
private:
    Item value;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(Item item):value(item), left(NULL), right(NULL) {}
    Item getValue() {
        return value;
    }
    TreeNode* getLeft() {
        return left;
    }
    TreeNode* getRight() {
        return right;
    }
    void setLeft(TreeNode*  node) {
        left = node;
    }
    void setRight(TreeNode* node) {
        right = node;
    }
};

template <typename Item>
class BST {
private:
    typedef TreeNode<Item> Node;
    Node* root;
public:
    BST(Item item) {
        root = new Node(item);
    }
    void insertKey(Item item) {
        if (!root) {
            root = new Node(item);
            return;
        }
        if (item < root->getValue())
            root->getLeft()->insertKey(item);
        else if (item > root->getValue())
            root->getRight()->insertkey(item);
    }
};

template <typename KeyType>
class BTreeNode {
private:
    int n; // number of keys stored in this node;
    bool isLeaf;
    KeyType* keys;
    BTreeNode* parent;
    BTreeNode** children;
public:
    BTreeNode(int L) {
        auto keys = new KeyType[L * 2 - 1];
        n = 0;
        isLeaf = true;
        parent = NULL;
        children = NULL;
    }
};

template <typename KeyType>
class BTree {
private:
    typedef BTreeNode<KeyType> BNode;
    typedef BNode* BNodeLink;
    BNodeLink root;
    int L;
public:
    BTree(int LVal):L(LVal) {
        BNodeLink root = new BNode(LVal);
    }
    ~BTree(){}
    BNodeLink searchKey(KeyType key);
    void insertKey(KeyType key);
    void deleteKey(KeyType key);

};


#endif //GRAPHBASIC_MAGICTREE_H
