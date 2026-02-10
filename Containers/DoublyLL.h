//
// Created by asus on 2/9/2026.
//


#pragma once

template <typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

  
    T* pushBack(const T& value);


    void remove(Node* node);
    int getSize() const;
    bool isEmpty() const;

    Node* getHead() const;
    Node* getTail() const;
    void clear();
};
