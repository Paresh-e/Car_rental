//
// Created by asus on 2/9/2026.
//
#ifndef AVL_TREE_CPP
#define AVL_TREE_CPP
#include "AVL.h"

template <class T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
}

template <class T>
AVLTree<T>::~AVLTree()
{
}
template <class T>
int AVLTree<T>::height(AVLNode<T>* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}
template <class T>
int AVLTree<T>::getBalance(AVLNode<T>* node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
template <class T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* y)
{
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
template <class T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* x)
{
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}
template <class T>
AVLNode<T>* AVLTree<T>::insertNode(AVLNode<T>* node, string key, T value)
{
    if (node == nullptr)
        return new AVLNode<T>(key, value);

    if (key < node->key)
        node->left = insertNode(node->left, key, value);
    else if (key > node->key)
        node->right = insertNode(node->right, key, value);
    else
    {
        node->value = value; 
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

 
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <class T>
void AVLTree<T>::insert(string key, T value)
{
    root = insertNode(root, key, value);
}
template <class T>
AVLNode<T>* AVLTree<T>::searchNode(AVLNode<T>* node, string key)
{
    if (node == nullptr || node->key == key)
        return node;

    if (key < node->key)
        return searchNode(node->left, key);
    else
        return searchNode(node->right, key);
}
template <class T>
T AVLTree<T>::search(string key)
{
    AVLNode<T>* node = searchNode(root, key);
    if (node == nullptr)
        return nullptr;
    return node->value;
}
template <class T>
void AVLTree<T>::inorderDisplay(AVLNode<T>* node)
{
    if (node != nullptr)
    {
        inorderDisplay(node->left);
        cout << node->key << " ";
        inorderDisplay(node->right);
    }
}
template <class T>
void AVLTree<T>::displayInOrder()
{
    inorderDisplay(root);
    cout << endl;
}
template <class T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
    AVLNode<T>* current = node;

    while (current->left != nullptr)
        current = current->left;
    return current;
}

template <class T>
AVLNode<T>* AVLTree<T>::deleteNode(AVLNode<T>* node, string key) {
    if (node == nullptr)
        return node;

  
    if (key < node->key)
        node->left = deleteNode(node->left, key);
    else if (key > node->key)
        node->right = deleteNode(node->right, key);
    else {
       
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode<T>* temp = node->left ? node->left : node->right;

           
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
               
                *node = *temp;
            }
            delete temp;
        } else {
            
            AVLNode<T>* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    
    if (node == nullptr)
        return node;

    
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

 
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

   
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <class T>
void AVLTree<T>::remove(string key) {
    root = deleteNode(root, key);
}

#endif