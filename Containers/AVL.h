//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_AVL_H
#define CAR_RENTAL_AVL_H
#include <iostream>
#include <string>
using namespace std;
template <class T>
class AVLNode
{
public:
    string key; 
    T value;    
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
    AVLNode(string k = "", T v = nullptr)
    {
        key = k;
        value = v;
        left = right = nullptr;
        height = 1;
    }
};

template <class T>
class AVLTree
{
private:
    AVLNode<T>* root;

    AVLNode<T>* insertNode(AVLNode<T>* node, string key, T value);
    AVLNode<T>* rotateRight(AVLNode<T>* y);
    AVLNode<T>* rotateLeft(AVLNode<T>* x);
    int height(AVLNode<T>* node);
    int getBalance(AVLNode<T>* node);
    AVLNode<T>* minValueNode(AVLNode<T>* node);
    AVLNode<T>* deleteNode(AVLNode<T>* node, string key);
    AVLNode<T>* searchNode(AVLNode<T>* node, string key);

    void inorderDisplay(AVLNode<T>* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(string key, T value);
    void remove(string key);
    T search(string key);
    void displayInOrder();
};

#include "AVL.cpp"
#endif 