#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class MinHeap
{
private:
    T* data;
    int capacity;
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap(int capacity = 100);
    ~MinHeap();

    void push(const T& value);
    T pop();
    T peek() const;

    bool isEmpty() const;
    bool isFull() const;
};


//#include "MinHeap.cpp"  // مهم!

#endif
