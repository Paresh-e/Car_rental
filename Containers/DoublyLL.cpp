
#include "DoublyLL.h"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    head = tail = nullptr;
    size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

template <typename T>
T* DoublyLinkedList<T>::pushBack(const T& value)
{
    Node* newNode = new Node{value, tail, nullptr};

    if (tail)
        tail->next = newNode;
    else
        head = newNode;

    tail = newNode;
    size++;
    return &newNode->data;
}
template <typename T>
void DoublyLinkedList<T>::remove(Node* node)
{
    if (!node) return;

    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    delete node;
    size--;
}
template <typename T>
typename DoublyLinkedList<T>::Node*
DoublyLinkedList<T>::getHead() const
{
    return head;
}
template <typename T>
int DoublyLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    Node* curr = head;
    while (curr)
    {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}