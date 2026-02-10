#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class MinHeap {
private:
    vector<T> heap;

    int parent(int i);
    int left(int i);
    int right(int i);

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    bool empty() const;
    int size() const;

    void insert(const T& value);
    T getMin() const;
    T extractMin();
    void printHeap() const;
};

#include "MinHeap.cpp"  // مهم!

#endif
