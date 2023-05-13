#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue() = default;
    PriorityQueue(int cap);
    PriorityQueue(const std::vector<T>&);
    ~PriorityQueue() = default;

public:
    bool empty() const;

    T& findMin();
    const T& findMin() const;

public:
    void insert(const T&);
    void insert(T&&);

    void deleteMin();
    void deleteMin(T&);

    void clear();

public:
    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& rhs) {
        os << "[ ";
        for (int i = 0; i < rhs.m_size; ++i) {
            os << rhs.m_heap[i] << " ";
        }
        os << "]";
    }

private:
    void buildHeap();
    void percolateDown(int);

private:
    int m_size;
    std::vector<T> m_heap;
};

#include "PriorityQueue.hpp"
#endif // PRIORITY_QUEUE_H

