#include "PriorityQueue.h"

template <typename T>
PriorityQueue<T>::PriorityQueue(int cap)
: m_size{0}, m_heap(cap) {}

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& rhs)
: m_size{rhs.size()}, m_heap(rhs.size() + 10) {
    for (int i = 0; i < rhs.size(); ++i) {
        m_heap[i + 1] = rhs[i];
    }
    buildHeap();
}

template <typename T>
bool PriorityQueue<T>::empty() const {
    return m_heap.empty();
}

template <typename T>
void PriorityQueue<T>::insert(T&& x) {
    if (m_size == m_heap.size() - 1) {
        m_heap.resize(m_size * 2);
    } 
    int hole = ++m_size;
    T copy = x;
    m_heap[0] = std::move(copy);
    for (; x < m_heap[hole / 2]; hole /= 2) {
        m_heap[hole] = m_heap[hole / 2];
    }
    m_heap[hole] = std::move(m_heap[0]);
}

template <typename T>
void PriorityQueue<T>::deleteMin() {
    if (empty()) {
        return;
    }
    m_heap[1] = std::move(m_heap[m_size--]);
    percolateDown(1);
}

template <typename T>
void PriorityQueue<T>::deleteMin(T& minItem) {
    if (empty()) {
        return;
    }
    minItem = std::move(m_heap[1]);
    m_heap[1] = std::move(m_heap[m_size--]);
    percolateDown(1);
}

template <typename T>
void PriorityQueue<T>::buildHeap() {
    for (int i = m_size / 2; i > 0; --i) {
        percolateDown(i);
    }
}

template <typename T>
void PriorityQueue<T>::percolateDown(int hole)
{
    int child = 0;
    T tmp = std::move(m_heap[hole]);

    for (; hole * 2 <= m_size; hole = child) {
        child = hole * 2;
        if (child != m_size && m_heap[child + 1] < m_heap[child]) {
            ++child;
        }
        if (m_heap[child] < tmp) {
            m_heap[hole] = std::move(m_heap[child]);
        } else {
            break;
        }
    }
    m_heap[hole] = std::move(tmp);
}

template <typename T>
void PriorityQueue<T>::insert(const T& x) {
    if (m_size == m_heap.size() - 1) {
        m_heap.resize(m_size * 2);
    } 
    int hole = ++m_size;
    T copy = x;
    m_heap[0] = std::move(copy);
    for (; x < m_heap[hole / 2]; hole /= 2) {
        m_heap[hole] = m_heap[hole / 2];
    }
    m_heap[hole] = std::move(m_heap[0]);
}

template <typename T>
void PriorityQueue<T>::clear() {
    m_heap.clear();
    m_size = 0;
}