#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <initializer_list>

template <typename T>
class queue {
public:
    queue();
    queue(std::initializer_list<T>);
    queue(const queue<T>&);
    queue(queue<T>&&);

    queue<T>& operator=(const queue<T>&);
    queue<T>& operator=(queue<T>&&);

    T& front(); // access the first element
    const T& front() const;

    T& back(); // access the last element
    const T& back() const;

    bool empty() const;
    size_t size() const;

    void push(const T&);
    void pop();

    void clear();
    void swap(queue<T>&);

public:
    template <typename X>
    friend std::ostream& operator<<(std::ostream& os, const queue<X>& rhs) {
        auto x = rhs.head;
        for (; x != nullptr; x = x->next) {
            os << x->val << " <= ";
        }
        os << "queue end";
        return os;
    }

private:
    struct Node {
        Node(const T& v = T(), Node* n = nullptr, Node* p = nullptr) 
        : val{v}, next{n}, prev{p} {}
        T val;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    size_t m_size;
};
#include "queue.hpp"
#endif // QUEUE_H