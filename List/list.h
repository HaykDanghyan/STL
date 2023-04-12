#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class List {
private:
    struct ListNode {
        ListNode() : value{}, next{nullptr}, prev{nullptr} {}
        ListNode(T v = T(), ListNode* n = nullptr, ListNode* p = nullptr) :
            value{v}, next{n}, prev{p} {}
        T value;
        ListNode* next;
        ListNode* prev;
    };
    ListNode* m_head;
    ListNode* m_tail;
    size_t m_size;

public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    friend class List<T>;
    public:
        iterator() : curr{nullptr} {}
        iterator(ListNode* rhs) : curr{rhs} {}
        iterator(const iterator& rhs): curr{rhs.curr} {}
        ~iterator() { curr = nullptr; }
        T& operator*() const { return curr->value; }
        T* operator->() const { return &(curr->value); }
        iterator& operator++() {
            curr = curr->next;
            return *this;
        }
        iterator& operator++(int) {
            iterator temp(*this);
            curr = curr->next;
            return temp;
        }
        iterator& operator--() {
            curr = curr->prev;
            return *this;
        }
        iterator& operator--(int) {
            iterator temp(*this);
            curr = curr->prev;
            return temp;
        }
        bool operator==(const iterator& rhs) {
            return curr == rhs.curr;
        }
        bool operator!=(const iterator& rhs) {
            return curr != rhs.curr;
        }
    private:
        ListNode* curr;
    };
public:
    List(); // constructs the list
    List(size_t, const T& = T());
    List(const List<T>&);
    List(List<T>&&);
    List(std::initializer_list<T>);

    ~List(); // destructs the list

    List<T>& operator=(const List<T>&); // assigns values to the container
    List<T>& operator=(List<T>&&);

    void assign(size_t, const T&); // assigns values to the container
    void assign(std::initializer_list<T>);

    T& front(); // access the first element
    const T& front() const;

    T& back(); // access the last element
    const T& back() const;

    bool empty() const; // checks whether the container is empty

    size_t size() const; // returns the number of elements

    void clear(); // clears the contents

    void push_back(const T&); // adds an element to the end
    void push_back(T&&);

    void push_front(const T&); // inserts an element to the beginning
    void push_front(T&&);
    
    void pop_back(); // removes the last element

    void pop_front(); // removes the first element

    void resize(size_t, const T& = T()); // changes the number of elements stored

    void reverse(); // reverses the order of the elements

    void merge(List<T>&); // merges two sorted lists
    void merge(List<T>&&);

public:
    friend std::ostream& operator<<(std::ostream& os, const List<T>& rhs) {
        ListNode* curr = rhs.m_head;
        while (curr) {
            std::cout << curr->value << " ";
            curr = curr->next;
        }
        return os;
    }

    iterator begin() const noexcept; // returns an iterator to the beginning
    iterator end() const noexcept; // returns an iterator to the end

    iterator rbegin() const noexcept; // returns a reverse iterator to the beginning
    iterator rend() const noexcept; // returns a reverse iterator to the end

    iterator erase(iterator); // erases the specified element from the container

    iterator insert(iterator, const T&);
    iterator insert(iterator, T&&);

};
#include "list.hpp"
#endif // LIST_H