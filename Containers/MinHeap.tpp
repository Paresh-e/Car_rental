#include <stdexcept>
#include <algorithm>
#include "MinHeap.h"

template <typename T>
MinHeap<T>::MinHeap(int capacity)
{
    this->capacity = capacity;
    size = 0;
    data = new T[capacity];
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    delete[] data;
}

template <typename T>
bool MinHeap<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
bool MinHeap<T>::isFull() const
{
    return size == capacity;
}

template <typename T>
void MinHeap<T>::push(const T& value)
{
    if (isFull())
        throw std::overflow_error("Heap is full");

    data[size] = value;
    heapifyUp(size);
    size++;
}

template <typename T>
T MinHeap<T>::peek() const
{
    if (isEmpty())
        throw std::underflow_error("Heap is empty");

    return data[0];
}

template <typename T>
T MinHeap<T>::pop()
{
    if (isEmpty())
        throw std::underflow_error("Heap is empty");

    T root = data[0];
    data[0] = data[size - 1];
    size--;
    heapifyDown(0);

    return root;
}

template <typename T>
void MinHeap<T>::heapifyUp(int index)
{
    int parent = (index - 1) / 2;

    while (index > 0 && data[index] < data[parent])
    {
        std::swap(data[index], data[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && data[left] < data[smallest])
            smallest = left;

        if (right < size && data[right] < data[smallest])
            smallest = right;

        if (smallest == index)
            break;

        std::swap(data[index], data[smallest]);
        index = smallest;
    }
}
