#include <iostream>
#include "MinHeap.h"
template <typename T>
int MinHeap<T>::parent(int i) {
    return (i - 1) / 2;
}

template <typename T>
int MinHeap<T>::left(int i) {
    return 2 * i + 1;
}

template <typename T>
int MinHeap<T>::right(int i) {
    return 2 * i + 2;
}

template <typename T>
void MinHeap<T>::heapifyUp(int i) {
    while (i != 0 && heap[parent(i)] > heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(int i) {
    int smallest = i;
    int l = left(i);
    int r = right(i);

    if (l < heap.size() && heap[l] < heap[smallest])
        smallest = l;

    if (r < heap.size() && heap[r] < heap[smallest])
        smallest = r;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

template <typename T>
bool MinHeap<T>::empty() const {
    return heap.empty();
}

template <typename T>
int MinHeap<T>::size() const {
    return heap.size();
}

template <typename T>
void MinHeap<T>::insert(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T>
T MinHeap<T>::getMin() const {
    if (heap.empty())
        throw runtime_error("Heap is empty");
    return heap[0];
}

template <typename T>
T MinHeap<T>::extractMin() {
    if (heap.empty())
        throw runtime_error("Heap is empty");

    T root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty())
        heapifyDown(0);

    return root;
}

template <typename T>
void MinHeap<T>::printHeap() const {
    for (const T& x : heap)
        cout << x << " ";
    cout << endl;
}
