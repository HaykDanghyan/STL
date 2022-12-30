#include "queue.h"

template <typename T>
queue<T>::queue() : head{nullptr}, tail{nullptr}, m_size{0} {}

template <typename T>
queue<T>::queue(std::initializer_list<T> init) : head{nullptr}, tail{nullptr}, m_size{0} {
    for (const auto& el : init) {
        push(el);
    }
}

template <typename T>
queue<T>::queue(const queue<T>& rhs) : head{nullptr}, tail{nullptr}, m_size{0} {
    if (!rhs.head) {
        return;
    }
    m_size = rhs.m_size;
    head = new Node(rhs.head->val);
    Node* tmp1 = head;
    Node* tmp2 = rhs.head->next;
    while (tmp2) {
        tmp1->next = new Node(tmp2->val);
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
        tail = tmp1;
    }
}

template <typename T>
queue<T>::queue(queue<T>&& rhs): head{nullptr}, tail{nullptr}, m_size{0} {
    head = std::move(rhs.head);
    tail = std::move(rhs.tail);
    m_size = rhs.m_size;
    rhs.m_size = 0;
}

template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& rhs) {
    if (this != &rhs) {
        if (!rhs.head) {
            return *this;
        }
        head = new Node(rhs.head->val);
        Node* tmp1 = head;
        Node* tmp2 = rhs.head->next;
        while (tmp2) {
            tmp1->next = new Node(tmp2->val);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
            tail = tmp1;
        }
    }
    return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue<T>&& rhs) {
    if (this != &rhs) {
        head = std::move(rhs.head);
        tail = std::move(rhs.tail);
        m_size = rhs.m_size;
        rhs.m_size = 0;
    }
    return *this;
}

template <typename T>
void queue<T>::push(const T& val) {
    if (head == nullptr) {
        head = new Node(val);
        tail = head;
        ++m_size;
    } else {
        tail->next = new Node(val, nullptr, tail);
        tail = tail->next;
        ++m_size;        
    } 
}

template <typename T>
void queue<T>::pop() {
    if (!head) {
        return;
    }
    Node* del = head;
    head = head->next;
    delete del;
    del = nullptr;
    --m_size;
}

template <typename T>
T& queue<T>::front() {
    return head->val;
}

template <typename T>
const T& queue<T>::front() const {
    return head->val;
}

template <typename T>
T& queue<T>::back() {
    return tail->val;
}

template <typename T>
const T& queue<T>::back() const {
    return tail->val;
}

template <typename T>
bool queue<T>::empty() const {
    return head == nullptr;
}

template <typename T>
size_t queue<T>::size() const {
    return m_size;
}

template <typename T>
void queue<T>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        tmp = nullptr;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

template <typename T>
void queue<T>::swap(queue<T>& rhs) {
    using std::swap;
    swap(head, rhs.head);
    swap(tail, rhs.tail);
} 