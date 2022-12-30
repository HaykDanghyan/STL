#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>

template <typename T>
class forward_list {
private:
    struct Node {
        Node() : value{} , next {nullptr} {}
        Node(T val) : value{val} , next{nullptr} {}
        Node(T val, Node* ptr) : value{val} , next{ptr} {}
        T value;
        Node* next;
    };
    Node* head;
public:

    forward_list(); 
    forward_list(size_t);
    forward_list(size_t, const T&);
    forward_list(const forward_list&);
    forward_list(forward_list&&);
    forward_list(std::initializer_list<T>);
    ~forward_list();

public:

    forward_list& operator = (const forward_list&);
    forward_list& operator = (forward_list&&);
    forward_list& operator = (std::initializer_list<T>);

public:
    void clear() noexcept ;
    void swap(forward_list&) noexcept;
    forward_list assign(size_t, T);
    forward_list assign(std::initializer_list<T>);
    const T& front() const;
    bool empty() const;
    size_t max_size();
    void insert_after(size_t, const T&);
    void insert_after(size_t, size_t, const T&);
    void erase_after(size_t);
    void push_front(const T&);
    void pop_front();
    void sort();
    void reverse();

public:

    bool operator == (const forward_list&) const;
    bool operator != (const forward_list&) const;
    bool operator <  (const forward_list&) const;
    bool operator >  (const forward_list&) const;
    bool operator <= (const forward_list&) const;
    bool operator >= (const forward_list&) const;

public:
    friend std::ostream& operator << (std::ostream& os, const forward_list<T>& f1) {
        Node* curr = f1.head;
        while(curr != nullptr) {
            os << curr -> value << " -> ";
            curr = curr -> next;
        }
        std::cout << "nullptr";
        return os;
    }

public:
class forward_iterator : public std::iterator<std::forward_iterator_tag, T> {
private:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

private:
    Node* m_it;

public:
    forward_iterator() : m_it(nullptr) { }
    forward_iterator(Node* ptr) : m_it(ptr) { }
    reference operator*() const {
        return m_it -> value;
    }
    pointer operator ->() {
        return &(m_it -> value);
    }
    forward_iterator& operator++() {
        m_it = m_it -> next;
        return *this;
    }
    forward_iterator operator++(int) {
        forward_iterator tmp(m_it);
        m_it = m_it -> next;
        return tmp;
    }
    bool operator==(const forward_iterator& oth) {
        return m_it == oth.m_it;
    }
    bool operator !=(const forward_iterator& oth) {
        return !(*this == oth);
    }
};

public:
    forward_iterator begin() noexcept {
        return forward_iterator(head);
    }

    forward_iterator end() const noexcept {
        return forward_iterator(nullptr);
    }
};

#include "impl.hpp"
#endif
