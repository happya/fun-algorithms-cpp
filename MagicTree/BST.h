//
// Created by yyi on 2019/10/11.
//

#ifndef MAGICTREE_BST_H
#define MAGICTREE_BST_H


//
// Created by yyi on 2019/10/11.
//
#include <iostream>
using namespace std;

template <typename T>
class BSTNode {
private:
    typedef BSTNode<T> TreeNode;
public:
    T key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    BSTNode(T val) : key(val), left(NULL), right(NULL), parent(NULL) {};
};

template <typename T>
class BST {
private:
    typedef BSTNode<T> TreeNode;
    TreeNode* root;
    void insertNode(TreeNode* &tree, TreeNode* node);
    void preOrder(TreeNode* &node) const;
    void inOrder(TreeNode* &node) const;
    void postOrder(TreeNode* &node) const;
public:
    BST() : root(NULL) {}
    void preOrder();
    void inOrder();
    void postOrder();
    void insertKey(T val);

};


template <typename T>
void BST<T> :: insertNode(TreeNode* &tree, TreeNode* node) {
    TreeNode* parent = NULL;
    TreeNode* cur = tree;
    while(cur != NULL) {
        parent = cur;
        if (node->key > cur->key)
            cur = cur->right;
        else
            cur = cur->left;
    }
    node->parent = parent;
    if (parent == NULL)
        tree = node;
    else if (node->key > parent->key)
        parent->right = node;
    else
        parent->left = node;
}

template <typename T>
void BST<T> :: insertKey(T val) {
    auto node = new TreeNode(val);
    insertNode(root, node);
}

template <typename T>
void BST<T> :: preOrder(TreeNode* &node) const {
    if (node) {
        cout<<node->key<<" ";
        preOrder(node->left);
        preOrder(node->right);
    }
}
template <typename T>
void BST<T> :: preOrder() {
    preOrder(root);
}

template <typename T>
void BST<T> :: inOrder(TreeNode* &node) const {
    if (node) {
        inOrder(node->left);
        cout<<node->key<< " ";
        inOrder(node->right);
    }
}
template <typename T>
void BST<T> :: inOrder() {
    inOrder(root);
}

template <typename T>
void BST<T> :: postOrder(TreeNode* &node) const {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        cout<<node->key<<" ";
    }
}

template <typename T>
void BST<T> ::postOrder() {
    postOrder(root);
}
#endif //MAGICTREE_BST_H
